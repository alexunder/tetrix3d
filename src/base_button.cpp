// Foundation Research CopyRight @

#include "stdafx.h"
#include "base_button.h"

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

BOOL DrawMyRect(HDC hdc, RECT *lprc, COLORREF c1, COLORREF c0 )
{
	int x0 = lprc->left;
	int y0 = lprc->top;

	int x1 = lprc->right;
	int y1 = lprc->bottom;

	int d = 3;

	GradientRectangle(hdc, x0, y0, x1, y1, c1, c0, 45);
	GradientRectangle(hdc, x0+d, y0+d, x1-d, y1-d, c0, c1, 45);	

	return TRUE;
}

base_button::base_button()
{
	m_iStartx = 0;
	m_iStarty = 0;
	m_iwidth  = 0;
	m_iheight = 0;
	m_pfCommandFunction = NULL;
	m_enum_state = BUTTON_UNTOUCH;
}

base_button::~base_button()
{

}

bool base_button::Create(int x, int y, int width, int height)
{
	m_iStartx = x;
	m_iStarty = y;
	m_iwidth  = width;
	m_iheight = height;

	return true;
}

void base_button::Draw(HDC hdc)
{
	COLORREF color_brush = 0;
	RECT rect;
	HBRUSH hbrush = NULL;

	rect.left   = m_iStartx;
	rect.top    = m_iStarty;
	rect.right  = rect.left + m_iwidth;
	rect.bottom = rect.top  + m_iheight;

	switch( m_enum_state )
	{
	case BUTTON_UNTOUCH:
		{
			color_brush = RGB(61,89,171);
		}
		break;
	case BUTTON_TOUCH:
		{
			color_brush = RGB(30, 144, 255);
		}
		break;
	case BUTTON_PUSH:
		{
			color_brush = RGB(0,0,255);
			rect.top++;
			rect.bottom++;
		}
		break;
	case BUTTON_DISABLE:
		{
			color_brush = RGB(128,138,135);
		}
		break;
	}	

	//hbrush = CreateSolidBrush( color_brush );
	//FillRect( hdc, &rect, hbrush );
	//DeleteObject(hbrush);
	DrawMyRect(hdc, &rect, color_brush, RGB(0xff,0xff,0xff));

	rect.top = rect.top + 5;
	int oldmode = SetBkMode( hdc, TRANSPARENT );
	DrawText( hdc, TEXT("Start Game"), -1, &rect, DT_CENTER | DT_VCENTER );
	SetBkMode( hdc, oldmode );
}
	
bool base_button::isPointIn(int x,int y)
{
	return ( x >= m_iStartx && x < m_iStartx + m_iwidth &&
		     y >= m_iStarty && y < m_iStarty + m_iheight );
}
	
void base_button::ChangeState(enum_button_state state)
{
	m_enum_state = state;
}
	
void base_button::LeftButtonDown(int x,int y)
{
	m_enum_state = BUTTON_PUSH;
}
	
void base_button::LeftButtonUp(int x, int y)
{
	m_enum_state = BUTTON_TOUCH;

	if(m_pfCommandFunction != NULL)
	{
		m_pfCommandFunction( this );
	}
}
	
void base_button::MouseMove(int x, int y)
{
	m_enum_state = BUTTON_TOUCH;
}
