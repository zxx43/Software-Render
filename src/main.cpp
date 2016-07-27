#include <windows.h>
#include "frame.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
const TCHAR szName[]=TEXT("win");
HDC hdc,dibDC;
HBITMAP screenDIB=NULL,dibBefore;
int swidth,sheight;
BOOL mode256=false;
HPALETTE hPalette=NULL;

void initDIB(HDC dibDC,int width,int height) {
	BITMAPINFO bmi;
	memset(&bmi,0,sizeof(bmi));
	bmi.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth=width;
	bmi.bmiHeader.biHeight=-height;
	bmi.bmiHeader.biPlanes=1;
	bmi.bmiHeader.biBitCount=24;
	bmi.bmiHeader.biCompression=BI_RGB;
	screenDIB=CreateDIBSection(NULL,&bmi,DIB_RGB_COLORS,(void**)&screenBits,NULL,0);
	dibBefore=(HBITMAP)SelectObject(dibDC,screenDIB);
}
void releaseDIB(HDC dibDC) {
	if(screenDIB!=NULL) {
		SelectObject(dibDC,dibBefore);
		DeleteObject(screenDIB);
		screenDIB=NULL;
	}
}

void checkDisplayMode(HDC hdc) {
	int palSize=GetDeviceCaps(hdc,SIZEPALETTE);
	if(palSize==256)
		mode256=true;
}
void createPalette(HDC hdc) {
	if(!mode256)
		return;
	printf("create palette\n");
//	hPalette=CreateHalftonePalette(hdc);
	int i=0,incr=8,red=0,green=0,blue=0;
	LOGPALETTE* plp=(LOGPALETTE*)malloc(sizeof(LOGPALETTE)+246*sizeof(PALETTEENTRY));
	plp->palVersion=0x0300;
	plp->palNumEntries=247;
	for(green=0;green<=255;green+=incr) {
		plp->palPalEntry[i].peRed=(BYTE)green;
		plp->palPalEntry[i].peGreen=(BYTE)green;
		plp->palPalEntry[i].peBlue=(BYTE)green;
		plp->palPalEntry[i].peFlags=0;
		incr=(incr==9)?8:9;
		i++;
	}
	for(red=0;red<=255;red+=51) {
		for(green=0;green<=255;green+=51) {
			for(blue=0;blue<=255;blue+=51) {
				plp->palPalEntry[i].peRed=(BYTE)red;
				plp->palPalEntry[i].peGreen=(BYTE)green;
				plp->palPalEntry[i].peBlue=(BYTE)blue;
				plp->palPalEntry[i].peFlags=0;
				i++;
			}
		}
	}
	hPalette=CreatePalette(plp);
	free(plp);
}
void releasePalette() {
	if(hPalette) {
		DeleteObject(hPalette);
		hPalette=NULL;
		printf("release palette\n");
	}
}

void killWindow(HWND hWnd,HINSTANCE hInstance,WNDCLASS wndClass) {
	release();
	DestroyWindow(hWnd);
	UnregisterClass(wndClass.lpszClassName,hInstance);
}

void runWindow() {
	act();
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR szCmdLine,int iCmdShow) {
	HWND hWnd;
	MSG msg;
	WNDCLASS wndClass;

	wndClass.style=CS_HREDRAW|CS_VREDRAW;
	wndClass.lpfnWndProc=WndProc;
	wndClass.cbClsExtra=0;
	wndClass.cbWndExtra=0;
	wndClass.hInstance=hInstance;
	wndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName=NULL;
	wndClass.lpszClassName=szName;

	if(!RegisterClass(&wndClass)) {
		MessageBox(NULL,TEXT("Can not create!"),szName,MB_ICONERROR);
		return 0;
	}

	hWnd=CreateWindow(szName,TEXT("Soft Render"),WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,CW_USEDEFAULT,SCREEN_WIDTH,SCREEN_HEIGHT,
			NULL,NULL,hInstance,NULL);
	hdc=GetDC(hWnd);
	checkDisplayMode(hdc);
	createPalette(hdc);
	dibDC=CreateCompatibleDC(hdc);
	swidth=SCREEN_WIDTH;
	sheight=SCREEN_HEIGHT;
	init();

	ShowWindow(hWnd,iCmdShow);
	UpdateWindow(hWnd);
	willExit=false;
	memset(&msg,0,sizeof(MSG));

	if(hPalette) {
		SelectPalette(hdc,hPalette,FALSE);
		RealizePalette(hdc);
	}

	while(!willExit) {
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {
			if(msg.message==WM_QUIT)
				willExit=true;
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else {
			runWindow();
			draw();
			BitBlt(hdc,0,0,swidth,sheight,dibDC,0,0,SRCCOPY);
		}
	}

	releasePalette();
	releaseDIB(dibDC);
	DeleteDC(dibDC);
	ReleaseDC(hWnd,hdc);
	killWindow(hWnd,hInstance,wndClass);
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam) {
	switch(msg) {
		case WM_SIZE:
			swidth=LOWORD(lParam); sheight=HIWORD(lParam);
			resize(LOWORD(lParam),HIWORD(lParam));
			releaseDIB(dibDC);
			initDIB(dibDC,LOWORD(lParam),HIWORD(lParam));
			InvalidateRect(hWnd,NULL,FALSE);
			break;
		case WM_KEYDOWN:
			keyDown(wParam);
			break;
		case WM_KEYUP:
			keyUp(wParam);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_QUERYNEWPALETTE:
			if(!hPalette)
				break;
			SelectPalette(hdc,hPalette,FALSE);
			RealizePalette(hdc);
			InvalidateRect(hWnd,NULL,FALSE);
			break;
		case WM_PALETTECHANGED:
			if(!hPalette||(HWND)wParam==hWnd)
				break;
			SelectPalette(hdc,hPalette,FALSE);
			RealizePalette(hdc);
			UpdateColors(hdc);
			break;
		default:
			return DefWindowProc(hWnd,msg,wParam,lParam);
	}

	return 0;
}
