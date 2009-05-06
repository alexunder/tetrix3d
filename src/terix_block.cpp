//Second Foundation Copyright @

#include "tetrix_block.h"

base_block::base_block()
{
	m_istart_x = 5;
	m_istart_y = 5;
}

base_block::~base_block()
{

}

void base_block::rotate()
{

}
	
void base_block::move_right()
{
	m_istart_x++;
}
	
void base_block::move_left()
{
	m_istart_x--;
}


void base_block::fall_slow()
{
	m_istart_y++;
}
	
void base_block::fall_fast()
{
	m_istart_y = m_istart_y + 4;
}
	
void base_block::draw( void * pcontext )
{

}

