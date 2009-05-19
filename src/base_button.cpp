// Foundation Research CopyRight @

#include "stdafx.h"
#include "base_button.h"

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

	hbrush = CreateSolidBrush( color_brush );
	FillRect( hdc, &rect, hbrush );
	DeleteObject(hbrush);

	DrawText( hdc, TEXT("Push me"), -1, &rect, DT_CALCRECT  );
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
