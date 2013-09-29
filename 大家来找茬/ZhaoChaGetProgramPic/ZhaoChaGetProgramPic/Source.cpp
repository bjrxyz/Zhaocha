/* ************************************
*����ͨWindows API��
* ʾ������
* PrtSrcn.c
* 13.7 ����
**************************************/
/* ͷ�ļ� */
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

HBITMAP ScreenCapture(LPSTR filename ,WORD BitCount,LPRECT lpRect);

/*************************************
* DWORD WINAPI WinMain(HINSTANCE hinstance,
HINSTANCE hPrevInstance,
LPSTR lpCmdLine,
int nCmdShow)
* ���� ����������Ϊ�ļ�������ʾ�ڴ�����
*
**************************************/
INT WINAPI WinMain(HINSTANCE hinstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine,
					 int nCmdShow)
{
	
	HWND hwndCap = NULL;
	int pointX,pointY;

	//  ofstream pointFile("d:\\point.txt");��
	   std::ifstream readfile;
	 //pointFile <<pointX;
	   readfile.open("d:\\point.txt",std::ios::in);
	   readfile  >>  pointX;

	    std::ifstream in("d:\\point.txt");  //�����ļ�
  in >> pointX;

   printf("sss\n");
	 printf("%d\n",pointX);

	 system("pause");
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

	// ��ȡ��Ļ���ɸ�����Ҫ���ò�ͬ�Ĳ���������ֻ��ʾ��ȡ�ض����ڡ�
	ghBitmap = ScreenCapture("taskmgr.bmp" ,32, &rectShow);

	
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
	hbmfile = CreateFile(L"pic.bmp",
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