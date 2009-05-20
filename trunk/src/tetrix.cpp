// tetrix.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "tetrix.h"
#include "tetrix_scene.h"
#include "base_button.h"
#include "win_gdi_help.h"

#define MAX_LOADSTRING 100

#define TIMER_BLOCK 1
#define TIMER_BLOCK_INTERVAL 1000

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HBITMAP g_blockbmp = NULL;
HWND g_hWnd;
RECT g_rect;
bool g_bisgameover = false;
//game scene
base_tetrix_scene g_scene;

base_button * g_pBtn = NULL;
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void btn_click( void * p )
{
	if ( p != NULL )
	{
		base_button * pbtn = (base_button*)p;
		pbtn->DisableButton();
		InvalidateRect( g_hWnd,  &g_rect, TRUE );
	}

	//MessageBox( NULL, TEXT("haha"), TEXT("info"), MB_OK );
	g_scene.StartGame();
	g_bisgameover = false;
	SetTimer(g_hWnd, TIMER_BLOCK, TIMER_BLOCK_INTERVAL, NULL );
}


void EndGame(void)
{
	if ( g_pBtn != NULL )
	{
		g_pBtn->EnableButton();
	}

	KillTimer( g_hWnd, TIMER_BLOCK );
	g_bisgameover = true;
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

	g_scene.CreateScene( 12, 22, EndGame );

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
	wcex.hbrBackground	= (HBRUSH)GetStockObject( NULL_BRUSH );
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
   g_pBtn->Create(340, 530, 120, 30);
   g_pBtn->m_pfCommandFunction = btn_click;
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

			HDC hmemDC = CreateCompatibleDC( hdc );
			HBITMAP hbkg = CreateCompatibleBitmap( hdc, 500, 600 );
			HGDIOBJ oldj = SelectObject(hmemDC, hbkg);

			//FillRect( hmemDC, &g_rect, (HBRUSH)GetStockObject(BLACK_BRUSH) );
			DrawGradientRect(hmemDC, &g_rect, RGB(0xff,0xff,0xff), RGB(0,0,0), 0);
			
			//Draw frame
			//Moveto()
			int istartx = 20;
			int istarty = 20;
			MoveToEx(hmemDC, istartx, istarty, NULL );
			LineTo(hmemDC, istartx + 12*23, istarty);
			LineTo(hmemDC, istartx + 12*23, istarty + 22*23);
			LineTo(hmemDC, istartx,         istarty + 22*23);
			LineTo(hmemDC, istartx,         istarty);
			// TODO: Add any drawing code here...
			if ( g_blockbmp != NULL )
			{
				for ( int i = 0; i < 22; i++ )
					for ( int j = 0; j < 12; j++ )
					{
						if(g_scene.isOneGridNeedShow(j + 12*i) )
						{
							DrawBitmap( hmemDC, g_blockbmp, 20 + 23*j , 20 + 23*i );
						}
					}
			}

			if(g_pBtn != NULL)
			{
				g_pBtn->Draw(hmemDC);
			}

			if ( g_bisgameover == true )
			{
				LOGFONT tFont;
				memset( &tFont, 0, sizeof(LOGFONT) );
				wcsncpy( tFont.lfFaceName, TEXT("Consolas"), LF_FACESIZE );
				tFont.lfHeight = 50;
				tFont.lfWeight = 700;
				RECT trect;
				trect.left   = istartx;
				trect.top    = istarty + 150;
				trect.right  = trect.left + 12*23;
				trect.bottom = trect.top  + 22*23;
				HFONT hf = CreateFontIndirect( &tFont );
				HGDIOBJ old = SelectObject( hmemDC, hf );
				int oldmode = SetBkMode( hmemDC, TRANSPARENT );
				DrawText( hmemDC, TEXT("Game Over!!"), -1, &trect, DT_CENTER | DT_VCENTER );
				SetBkMode( hdc, oldmode );
				DeleteObject(hf);
			}

			BitBlt( hdc, 0, 0, 500, 600, hmemDC, 0, 0, SRCCOPY );

			SelectObject(hmemDC, oldj);
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
	case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_LEFT:
				{
					g_scene.user_left();
				}
				break;
			case VK_RIGHT:
				{
					g_scene.user_right();
				}
				break;
			case VK_UP:
				{
					g_scene.user_rotate();
				}
				break;
			case VK_DOWN:
				{
					g_scene.user_down();
				}
				break;
			case VK_SPACE:
				{
					g_scene.user_fall();
				}
				break;
			}

			InvalidateRect( g_hWnd,  &g_rect, TRUE );
		}
		break;
	case WM_TIMER:
		{
			if(wParam == TIMER_BLOCK)
			{
				g_scene.user_down();
				InvalidateRect( g_hWnd,  &g_rect, TRUE );
			}
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

		KillTimer(g_hWnd, TIMER_BLOCK);

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
