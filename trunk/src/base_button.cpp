// Foundation Research CopyRight @

#include "stdafx.h"
#include "base_button.h"
#include "win_gdi_help.h"

base_button::base_button()
{
	m_iStartx = 0;
	m_iStarty = 0;
	m_iwidth  = 0;
	m_iheight = 0;
	m_pfCommandFunction = NULL;
	m_enum_state = BUTTON_UNTOUCH;
	m_isenable = 1;
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
	COLORREF color2      = 0;
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
			color2 = RGB(0xff,0xff,0xff);
		}
		break;
	case BUTTON_TOUCH:
		{
			color_brush = RGB(30, 144, 255);
			color2 = RGB(0xff,0xff,0xff);
		}
		break;
	case BUTTON_PUSH:
		{
			color_brush = RGB(0,0,255);
			color2 = RGB(0xff,0xff,0xff);
			rect.top++;
			rect.bottom++;
		}
		break;
	case BUTTON_DISABLE:
		{
			color_brush = RGB(128,138,135);
			color2 = RGB(0 ,0 ,0);
		}
		break;
	}	

	//hbrush = CreateSolidBrush( color_brush );
	//FillRect( hdc, &rect, hbrush );
	//DeleteObject(hbrush);
	DrawGradientRect(hdc, &rect, color_brush, color2, 0);

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
	if ( m_isenable == 0 )
	{
		return;
	}

	m_enum_state = state;
}
	
void base_button::LeftButtonDown(int x,int y)
{
	if ( m_isenable == 0 )
	{
		return;
	}

	m_enum_state = BUTTON_PUSH;
}
	
void base_button::LeftButtonUp(int x, int y)
{
	if ( m_isenable == 0 )
	{
		return;
	}

	m_enum_state = BUTTON_TOUCH;

	if(m_pfCommandFunction != NULL && m_isenable == 1)
	{
		this->m_pfCommandFunction( this );
	}
}
	
void base_button::MouseMove(int x, int y)
{
	if ( m_isenable == 0 )
	{
		return;
	}

	m_enum_state = BUTTON_TOUCH;
}
