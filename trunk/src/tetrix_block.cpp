//Second Foundation Copyright @
#include "stdafx.h"
#include "tetrix_block.h"

void base_matrix_rotate_90_ckw( unsigned char * pMatrix, int dim )
{
	if( pMatrix == NULL )
	{
		return;		  
	}

	int i;
	int temp = 0;

	int start_index = 0;
	int end_index = dim - 1;

	for(;start_index < end_index; start_index++, end_index--)
	{
		for(i = start_index; i < end_index; i++)
		{
			temp = pMatrix[i+start_index*dim];
			pMatrix[i + start_index*dim] = pMatrix[start_index + (end_index - i + start_index)*dim];
			pMatrix[start_index + (end_index - i + start_index)*dim] = pMatrix[(end_index - i + start_index) + end_index*dim];
			pMatrix[(end_index - i + start_index) + end_index*dim]   = pMatrix[end_index + i*dim];
			pMatrix[end_index + i*dim]   = temp; 	
		}
	}
}

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
	base_matrix_rotate_90_ckw(m_data, 4);
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
	
void base_block::draw( scene_context * pcontext )
{
	if ( pcontext == NULL )
	{
		return;
	}
}

