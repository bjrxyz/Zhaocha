#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

/* �������� */
#define PALVERSION 0x300
#define CAP_SHOW_MODE_STRTCH 1
#define CAP_SHOW_MODE_NOSTRTCH 0

/* ȫ�ֱ��� */
HBITMAP ghBitmap = NULL;
RECT rectShow;
// �޸������ȡ��ͬ�Ĵ��ڣ����ΪNULL�����ȡ��Ļ
LPSTR szCaptureWindowName = "Windows ���������";

/* �������� */
BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize);
HBITMAP ScreenCapture(LPSTR filename ,WORD BitCount,LPRECT lpRect);

/*************************************
* DWORD WINAPI WinMain(HINSTANCE hinstance,
HINSTANCE hPrevInstance,
LPSTR lpCmdLine,
int nCmdShow)
* ���� ����������Ϊ�ļ�������ʾ�ڴ�����
*
**************************************/
int main()
{
	printf("��ʼ\n");
	system("pause");
	HWND hwndCap = NULL;
	int pointX,pointY;

	int count = 1;
	char fileName[100] = "d:\\zhaocha\\p0.bmp";
	//printf("(x,y):%s\n",fileName);
	
		// ��ȡȫ��Ļ���Ǵ���
	if(szCaptureWindowName != NULL)
	{
		//Windows ���������
		hwndCap = FindWindow(NULL,L"������Ҳ�");
		// ��ȡ���ڵ�RECT���������޸ģ���ȡ��Ļ�е���������
		if(!GetWindowRect(hwndCap,&rectShow))
		{
			MessageBox(NULL,L"Can not find window to capture", L"erroe",MB_OK);
			return 0;
		}
	}

	while (1)
	{
	

	fileName[12]++;
	printf("ͼƬfileName:%s\n",fileName);
	ghBitmap = ScreenCapture(fileName ,32, &rectShow);

	printf("ͼƬ�Ѿ����棬��������\n");
	system("pause");

	std::ifstream in("d:\\zhaocha\\point.txt");  //�����ļ�
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
* ���� ��ȡָ���������Ļ��������Ϊ�ļ�
*
* ����	LPSTR filename ����λͼ�ļ����ļ�·�������ΪNULL���򲻱���
*		WORD BitCount Bit��ȣ����ڱ�ʾһ�����ص���ʹ�õ����ݳ���
*		LPRECT lpRect �����ȡ����Ļ�������ΪNULL�����ȡȫ��Ļ
*
* ���� HBITMAP ����ȡ��λͼ����
**************************************/
HBITMAP ScreenCapture(LPSTR filename ,WORD BitCount,LPRECT lpRect)
{
	HBITMAP hBitmap;
	// ��ʾ����ĻDC
	HDC hScreenDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	HDC hmemDC = CreateCompatibleDC(hScreenDC);
	// ��ʾ����Ļ�Ŀ�͸�
	int ScreenWidth = GetDeviceCaps(hScreenDC, HORZRES);
	int ScreenHeight = GetDeviceCaps(hScreenDC, VERTRES);
	// �ɵ�BITMAP�������������ȡ��λ�ý���
	HBITMAP hOldBM;
	// ����λͼ����
	PVOID lpvpxldata;
	// ������ȡ�ĳ������
	INT ixStart;
	INT iyStart;
	INT iX;
	INT iY;
	// λͼ���ݴ�С
	DWORD dwBitmapArraySize;
	// ������С
	DWORD nBitsOffset;
	DWORD lImageSize ;
	DWORD lFileSize ;
	// λͼ��Ϣͷ
	BITMAPINFO bmInfo;
	// λͼ�ļ�ͷ
	BITMAPFILEHEADER bmFileHeader;
	// д�ļ���
	HANDLE hbmfile;
	DWORD dwWritten;

	// ���LPRECT ΪNULL ��ȡ������Ļ
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
	// ����BTIMAP
	hBitmap = CreateCompatibleBitmap(hScreenDC, iX, iY);
	// ��BITMAPѡ�����ڴ�DC��
	hOldBM = (HBITMAP)SelectObject(hmemDC, hBitmap);
	// BitBlt��ĻDC���ڴ�DC�����������ȡ�Ļ�ȡ���ò���
	BitBlt(hmemDC, 0, 0, iX, iY, hScreenDC, ixStart, iyStart, SRCCOPY);
	// ���ɵ�BITMAP����ѡ����ڴ�DC������ֵΪ���滻�Ķ��󣬼�����ȡ��λͼ
	hBitmap = (HBITMAP)SelectObject(hmemDC, hOldBM);
	if(filename == NULL)
	{
		DeleteDC( hScreenDC);
		DeleteDC(hmemDC);
		return hBitmap;
	}
	// Ϊλͼ���������ڴ�ռ�
	dwBitmapArraySize = ((((iX*32) + 31) & ~31)>> 3)* iY;
	lpvpxldata = HeapAlloc(GetProcessHeap(),HEAP_NO_SERIALIZE,dwBitmapArraySize);
	ZeroMemory(lpvpxldata,dwBitmapArraySize);

	// ��� BITMAPINFO �ṹ
	ZeroMemory(&bmInfo,sizeof(BITMAPINFO));
	bmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmInfo.bmiHeader.biWidth = iX;
	bmInfo.bmiHeader.biHeight = iY;
	bmInfo.bmiHeader.biPlanes = 1;
	bmInfo.bmiHeader.biBitCount = BitCount;
	bmInfo.bmiHeader.biCompression = BI_RGB;

	// ��� BITMAPFILEHEADER �ṹ
	ZeroMemory(&bmFileHeader,sizeof(BITMAPFILEHEADER));
	nBitsOffset = sizeof(BITMAPFILEHEADER) + bmInfo.bmiHeader.biSize;
	lImageSize =
		((((bmInfo.bmiHeader.biWidth * bmInfo.bmiHeader.biBitCount) + 31) & ~31)>> 3)
		* bmInfo.bmiHeader.biHeight;
	lFileSize = nBitsOffset + lImageSize;
	bmFileHeader.bfType = 'B'+('M'<<8);
	bmFileHeader.bfSize = lFileSize;
	bmFileHeader.bfOffBits = nBitsOffset;

	// ��ȡDIB����д�뵽�ļ�
	GetDIBits(hmemDC, hBitmap, 0, bmInfo.bmiHeader.biHeight,
		lpvpxldata, &bmInfo, DIB_RGB_COLORS);
	// д�ļ�
	//wchar_t *text = new wchar_t[sizeof(wchar_t) * filename.size()];
	//MultiByteToWideChar(CP_ACP,0,filename,-1,text,filename.length());

	 wchar_t wText[30] = {L"����ʾ��"};
  
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

	// �ͷ��ڴ棬�����ͬ��DC��
	// ����û��ɾ��BITMAP����������ʾ��ɺ�ɾ��
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