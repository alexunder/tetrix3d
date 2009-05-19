// Foundation Research CopyRight @

#ifndef __H_BASE_BUTTON
#define __H_BASE_BUTTON

typedef enum _enum_button_state
{
	BUTTON_UNTOUCH,
	BUTTON_TOUCH,
	BUTTON_PUSH,
	BUTTON_DISABLE
}enum_button_state;

typedef void (*buttonclick)(void * p);

class base_button
{
public:
	base_button();
	~base_button();

	bool Create(int x, int y, int width, int height);

	void Draw(HDC hdc);
	bool isPointIn(int x,int y);
	void ChangeState(enum_button_state state);
	void LeftButtonDown(int x,int y);
	void LeftButtonUp(int x, int y);
	void MouseMove(int x, int y);
	void EnableButton()
	{
		m_isenable = 1;
		m_enum_state = BUTTON_UNTOUCH;
	}

	void DisableButton()
	{
		m_isenable = 0;
		m_enum_state = BUTTON_DISABLE;
	}
private:
	int m_iStartx;
	int m_iStarty;
	int m_iwidth;
	int m_iheight;
	enum_button_state m_enum_state;
	int m_isenable;
public:
	buttonclick m_pfCommandFunction;
};

#endif //__H_BASE_BUTTON
