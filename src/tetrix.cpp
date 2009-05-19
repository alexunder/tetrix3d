// tetrix.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "tetrix.h"
#include "tetrix_scene.h"
#include "base_button.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HBITMAP g_blockbmp = NULL;
HWND g_hWnd;
RECT g_rect;

//game scene
base_tetrix_scene g_scene;

base_button * g_pBtn = NULL;
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int DrawBitmap( HDC hDC, 
			   HBITMAP hBitmap, 
			   int x, 
			   int y )
{
	HDC hMemDC;
	HBITMAP hOldBmp;
	BITMAP bmp;
	int    bRet;

	hMemDC  = CreateCompatibleDC( hDC );
	hOldBmp = (HBITMAP)SelectObject( hMemDC, hBitmap );
	GetObject( hBitmap, sizeof( BITMAP ), &bmp );
	bRet    = BitBlt( hDC, x, y, bmp.bmWidth, bmp.bmHeight, hMemDC, 0, 0, SRCCOPY );
	SelectObject( hMemDC, hOldBmp );
	DeleteDC( hMemDC );

	return bRet;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TETRIXDEMO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	g_scene.CreateScene( 12, 22 );

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TETRIXDEMO));

	g_blockbmp = LoadBitmap( hInstance, MAKEINTRESOURCE(IDB_BLOCK));

	if ( g_hWnd != NULL )
	{
		GetClientRect( g_hWnd, &g_rect );
		InvalidateRect( g_hWnd,  &g_rect, TRUE );
	}
	
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TETRIXDEMO));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	//wcex.hbrBackground	= (HBRUSH)(GetStockObject(BLACK_BRUSH));
	wcex.lpszMenuName	= NULL/*MAKEINTRESOURCE(IDC_TETRIX)*/;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle,  
					   WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,
                       CW_USEDEFAULT, 0, 500, 600, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd; 

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   g_pBtn = new base_button;
   g_pBtn->Create(300, 50, 80, 20);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);

			HDC hmemDC = CreateCompatibleDC( NULL );
			HBITMAP hbkg = CreateCompatibleBitmap( hmemDC, 500, 600 );
			HGDIOBJ oldj = SelectObject(hmemDC, hbkg);

			FillRect( hmemDC, &g_rect, (HBRUSH)GetStockObject(BLACK_BRUSH) );
			// TODO: Add any drawing code here...
			if ( g_blockbmp != NULL )
			{
				for ( int i = 0; i < 22; i++ )
					for ( int j = 0; j < 12; j++ )
					{
						DrawBitmap( hmemDC, g_blockbmp, 20 + 23*j , 20 + 23*i );
					}
			}

			//if(g_pBtn != NULL)
			//{
			//	g_pBtn->Draw(hmemDC);
			//}

			BitBlt( hdc, 0, 0, 500, 600, hmemDC, 0, 0, SRCCOPY );

			SelectObject(hdc, oldj);
			DeleteObject(hbkg);
			DeleteDC( hmemDC );
			EndPaint(hWnd, &ps);
		}
		break;
	case WM_MOUSEMOVE:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			if(g_pBtn->isPointIn(x,y))
			{
				g_pBtn->MouseMove(x,y);
			}
			else
			{
				g_pBtn->ChangeState(BUTTON_UNTOUCH);
			}

			InvalidateRect( g_hWnd,  &g_rect, TRUE );
		}
		break;
	case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			if(g_pBtn->isPointIn(x,y))
			{
				g_pBtn->LeftButtonDown(x,y);
			}
			else
			{
				g_pBtn->ChangeState(BUTTON_UNTOUCH);
			}

			InvalidateRect( g_hWnd,  &g_rect, TRUE );
		}
		break;
	case WM_LBUTTONUP:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			if(g_pBtn->isPointIn(x,y))
			{
				g_pBtn->LeftButtonUp(x,y);
			}
			else
			{
				g_pBtn->ChangeState(BUTTON_UNTOUCH);
			}

			InvalidateRect( g_hWnd,  &g_rect, TRUE );
		}
		break;
	case WM_DESTROY:

		if( g_blockbmp != NULL )
		{
			DeleteObject(g_blockbmp);
			g_blockbmp = NULL;
		}

		if(g_pBtn != NULL)
		{
			delete g_pBtn;
		}

		g_scene.DestroyScene();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
