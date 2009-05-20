// Foundation Research CopyRight @
//gdi tool function in win32

#ifndef _H__WIN_GDI_HELP
#define _H__WIN_GDI_HELP

//draw the bitmap from HBITMAP
int DrawBitmap( HDC hDC, 
	 	HBITMAP hBitmap, 
		int x, 
		int y );

BOOL DrawGradientRect(HDC hdc, 
		      RECT *lprc, 
		      COLORREF color1, 
		      COLORREF color2,
	       	  int iEdgeWidth );

#endif //_H__WIN_GDI_HELP
