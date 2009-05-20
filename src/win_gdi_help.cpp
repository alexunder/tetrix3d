// Foundation Research CopyRight @

#include "stdafx.h"
#include "win_gdi_help.h"

#pragma comment(lib,"Msimg32.lib")

inline COLOR16 R16(COLORREF c) { return GetRValue(c)<<8; }
inline COLOR16 G16(COLORREF c) { return GetGValue(c)<<8; }
inline COLOR16 B16(COLORREF c) { return GetBValue(c)<<8; }

inline COLOR16 R16(COLORREF c0, COLORREF c1) { return ((GetRValue(c0)+GetRValue(c1))/2)<<8; }
inline COLOR16 G16(COLORREF c0, COLORREF c1) { return ((GetGValue(c0)+GetGValue(c1))/2)<<8; }
inline COLOR16 B16(COLORREF c0, COLORREF c1) { return ((GetBValue(c0)+GetBValue(c1))/2)<<8; }

BOOL GradientRectangle(HDC hDC, int x0, int y0, int x1, int y1, COLORREF c0, COLORREF c1, int angle)
{
	TRIVERTEX vert[4] = { 
		{ x0, y0,  R16(c0), G16(c0), B16(c0), 0 },				//  0:c0         3:(c0+c1)/2
		{ x1, y1,  R16(c1), G16(c1), B16(c1), 0 },				//
		{ x0, y1,  R16(c0, c1), G16(c0, c1), B16(c0, c1), 0 },	//
		{ x1, y0,  R16(c0, c1), G16(c0, c1), B16(c0, c1), 0 }	//  2:(c0+c1)/2  1: c1
	};

	ULONG Index[] = { 0, 1, 2, 0, 1, 3};

	switch ( angle % 180 )
	{
	case   0: 
		return GradientFill(hDC, vert, 2, Index, 1, GRADIENT_FILL_RECT_H);

	case  45: 
		return GradientFill(hDC, vert, 4, Index, 2, GRADIENT_FILL_TRIANGLE);

	case  90: 
		return GradientFill(hDC, vert, 2, Index, 1, GRADIENT_FILL_RECT_V);

	case 135: 
		vert[0].x = x1;
		vert[3].x = x0;
		vert[1].x = x0;
		vert[2].x = x1;
		return GradientFill(hDC, vert, 4, Index, 2, GRADIENT_FILL_TRIANGLE);
	}

	return FALSE;
}

BOOL  DrawGradientRect(HDC hdc, 
		       RECT *lprc, 
		       COLORREF color1, 
		       COLORREF color2,
	       	       int iEdgeWidth )
{
	int x0 = lprc->left;
	int y0 = lprc->top;

	int x1 = lprc->right;
	int y1 = lprc->bottom;

	int d = iEdgeWidth;

	GradientRectangle(hdc, x0, y0, x1, y1, color2, color1, 45);
	GradientRectangle(hdc, x0+d, y0+d, x1-d, y1-d, color1, color2, 45);	

	return TRUE;
}

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
