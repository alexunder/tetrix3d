//Second Foundation Copyright @

#ifndef _H__TETRIX_BLOCK
#define _H__TETRIX_BLOCK

#include "tetrix_context.h"

class base_block
{
public:
	base_block();
	virtual ~base_block();

	virtual void rotate();
	virtual void move_right();
	virtual void move_left();
	virtual void fall_slow();
	virtual void fall_fast();
	virtual void draw( scene_context * pcontext );
protected:
	unsigned char m_data[16];
	int m_istart_x;
	int m_istart_y;
};


#endif
