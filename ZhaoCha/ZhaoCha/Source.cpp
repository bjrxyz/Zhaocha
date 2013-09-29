#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

/* 常量定义 */
#define PALVERSION 0x300
#define CAP_SHOW_MODE_STRTCH 1
#define CAP_SHOW_MODE_NOSTRTCH 0

/* 全局变量 */
HBITMAP ghBitmap = NULL;
RECT rectShow;
// 修改这里截取不同的窗口，如果为NULL，则截取屏幕
LPSTR szCaptureWindowName = "Windows 任务管理器";

/* 函数申明 */
BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize);
HBITMAP ScreenCapture(LPSTR filename ,WORD BitCount,LPRECT lpRect);

/*************************************
* DWORD WINAPI WinMain(HINSTANCE hinstance,
HINSTANCE hPrevInstance,
LPSTR lpCmdLine,
int nCmdShow)
* 功能 截屏，保存为文件，并显示在窗口上
*
**************************************/
int main()
{
	printf("开始\n");
	system("pause");
	HWND hwndCap = NULL;
	int pointX,pointY;

	int count = 1;
	char fileName[100] = "d:\\zhaocha\\p0.bmp";
	//printf("(x,y):%s\n",fileName);
	
		// 截取全屏幕还是窗口
	if(szCaptureWindowName != NULL)
	{
		//Windows 任务管理器
		hwndCap = FindWindow(NULL,L"大家来找茬");
		// 获取窗口的RECT，可自行修改，获取屏幕中的任意区域
		if(!GetWindowRect(hwndCap,&rectShow))
		{
			MessageBox(NULL,L"Can not find window to capture", L"erroe",MB_OK);
			return 0;
		}
	}

	while (1)
	{
	

	fileName[12]++;
	printf("图片fileName:%s\n",fileName);
	ghBitmap = ScreenCapture(fileName ,32, &rectShow);

	printf("图片已经保存，计算坐标\n");
	system("pause");

	std::ifstream in("d:\\zhaocha\\point.txt");  //读入文件
	in >> pointX;
	in >> pointY;
	in.close();
	printf("(x,y):%d   %d\n",pointX,pointY);
	//SendMessage(hwndCap,WM_LBUTTONDOWN,0,(pointY<<16)+pointX);		
	//SendMessage(hwndCap,WM_LBUTTONUP,0,(pointY<<16)+pointX);			
	::SetCursorPos(pointY + rectShow.left + 15,pointX + rectShow.top + 190);
					mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
					mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
	}
	 
	

}


/*************************************
* BITMAP ScreenCapture(LPSTR filename ,WORD BitCount,LPRECT lpRect);
* 功能 截取指定区域的屏幕，并保存为文件
*
* 参数	LPSTR filename 保存位图文件的文件路径，如果为NULL，则不保存
*		WORD BitCount Bit深度，用于表示一个像素点所使用的数据长度
*		LPRECT lpRect 所需截取的屏幕区域，如果为NULL，则获取全屏幕
*
* 返回 HBITMAP 所截取的位图对象
**************************************/
HBITMAP ScreenCapture(LPSTR filename ,WORD BitCount,LPRECT lpRect)
{
	HBITMAP hBitmap;
	// 显示器屏幕DC
	HDC hScreenDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	HDC hmemDC = CreateCompatibleDC(hScreenDC);
	// 显示器屏幕的宽和高
	int ScreenWidth = GetDeviceCaps(hScreenDC, HORZRES);
	int ScreenHeight = GetDeviceCaps(hScreenDC, VERTRES);
	// 旧的BITMAP，用于与所需截取的位置交换
	HBITMAP hOldBM;
	// 保存位图数据
	PVOID lpvpxldata;
	// 截屏获取的长宽及起点
	INT ixStart;
	INT iyStart;
	INT iX;
	INT iY;
	// 位图数据大小
	DWORD dwBitmapArraySize;
	// 几个大小
	DWORD nBitsOffset;
	DWORD lImageSize ;
	DWORD lFileSize ;
	// 位图信息头
	BITMAPINFO bmInfo;
	// 位图文件头
	BITMAPFILEHEADER bmFileHeader;
	// 写文件用
	HANDLE hbmfile;
	DWORD dwWritten;

	// 如果LPRECT 为NULL 截取整个屏幕
	if(lpRect == NULL)
	{
		ixStart = iyStart = 0;
		iX = ScreenWidth;
		iY =ScreenHeight;
	}
	else
	{
		ixStart = lpRect->left;
		iyStart = lpRect->top;
		iX = lpRect->right - lpRect->left;
		iY = lpRect->bottom - lpRect->top;
	}
	// 创建BTIMAP
	hBitmap = CreateCompatibleBitmap(hScreenDC, iX, iY);
	// 将BITMAP选择入内存DC。
	hOldBM = (HBITMAP)SelectObject(hmemDC, hBitmap);
	// BitBlt屏幕DC到内存DC，根据所需截取的获取设置参数
	BitBlt(hmemDC, 0, 0, iX, iY, hScreenDC, ixStart, iyStart, SRCCOPY);
	// 将旧的BITMAP对象选择回内存DC，返回值为被替换的对象，既所截取的位图
	hBitmap = (HBITMAP)SelectObject(hmemDC, hOldBM);
	if(filename == NULL)
	{
		DeleteDC( hScreenDC);
		DeleteDC(hmemDC);
		return hBitmap;
	}
	// 为位图数据申请内存空间
	dwBitmapArraySize = ((((iX*32) + 31) & ~31)>> 3)* iY;
	lpvpxldata = HeapAlloc(GetProcessHeap(),HEAP_NO_SERIALIZE,dwBitmapArraySize);
	ZeroMemory(lpvpxldata,dwBitmapArraySize);

	// 添充 BITMAPINFO 结构
	ZeroMemory(&bmInfo,sizeof(BITMAPINFO));
	bmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmInfo.bmiHeader.biWidth = iX;
	bmInfo.bmiHeader.biHeight = iY;
	bmInfo.bmiHeader.biPlanes = 1;
	bmInfo.bmiHeader.biBitCount = BitCount;
	bmInfo.bmiHeader.biCompression = BI_RGB;

	// 添充 BITMAPFILEHEADER 结构
	ZeroMemory(&bmFileHeader,sizeof(BITMAPFILEHEADER));
	nBitsOffset = sizeof(BITMAPFILEHEADER) + bmInfo.bmiHeader.biSize;
	lImageSize =
		((((bmInfo.bmiHeader.biWidth * bmInfo.bmiHeader.biBitCount) + 31) & ~31)>> 3)
		* bmInfo.bmiHeader.biHeight;
	lFileSize = nBitsOffset + lImageSize;
	bmFileHeader.bfType = 'B'+('M'<<8);
	bmFileHeader.bfSize = lFileSize;
	bmFileHeader.bfOffBits = nBitsOffset;

	// 获取DIB用于写入到文件
	GetDIBits(hmemDC, hBitmap, 0, bmInfo.bmiHeader.biHeight,
		lpvpxldata, &bmInfo, DIB_RGB_COLORS);
	// 写文件
	//wchar_t *text = new wchar_t[sizeof(wchar_t) * filename.size()];
	//MultiByteToWideChar(CP_ACP,0,filename,-1,text,filename.length());

	 wchar_t wText[30] = {L"函数示例"};
  
	 MByteToWChar(filename,wText,sizeof(wText)/sizeof(wText[0]));

	hbmfile = CreateFile(wText,
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if(hbmfile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL,L"create file error",L"error",MB_OK);
	}

	WriteFile(hbmfile,&bmFileHeader,sizeof(BITMAPFILEHEADER),&dwWritten,NULL);
	WriteFile(hbmfile,&bmInfo,sizeof(BITMAPINFO),&dwWritten,NULL);
	WriteFile(hbmfile,lpvpxldata,lImageSize,&dwWritten,NULL);
	CloseHandle(hbmfile);

	// 释放内存，清除不同的DC。
	// 这里没有删除BITMAP对象，需在显示完成后删除
	HeapFree(GetProcessHeap(),HEAP_NO_SERIALIZE,lpvpxldata);
	ReleaseDC(0, hScreenDC);
	DeleteDC(hmemDC);	
	return hBitmap;
}

 BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize)
  {
    // Get the required size of the buffer that receives the Unicode 
    // string. 
    DWORD dwMinSize;
    dwMinSize = MultiByteToWideChar (CP_ACP, 0, lpcszStr, -1, NULL, 0);
  
    if(dwSize < dwMinSize)
    {
     return FALSE;
    }
  
    
    // Convert headers from ASCII to Unicode.
    MultiByteToWideChar (CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize);  
    return TRUE;
  }