//Second Foundation Copyright @

#include "stdafx.h"
#include "tetrix_scene.h"

static int g_i_count = 0;

unsigned int GenerateRandomNumber( unsigned int start, unsigned int end )
{
	if(start >= end)
	{
		return 0;
	}
	srand( GetTickCount() + g_i_count*200 );

	g_i_count++;
	int num = end - start + 1;
	
	return ( (rand()/(RAND_MAX/num) ) + start);
}

base_tetrix_scene::base_tetrix_scene()
{
	m_pcontext_freeze   = NULL;
	m_pcontext_activity = NULL;
	m_pblock = NULL;
}

base_tetrix_scene::~base_tetrix_scene()
{
	if(m_pcontext_freeze != NULL)
	{
		DestroySceneContext(m_pcontext_freeze);
		m_pcontext_freeze = NULL;
	}

	if(m_pcontext_activity != NULL)
	{
		DestroySceneContext(m_pcontext_activity);
		m_pcontext_activity = NULL;
	}

	if(m_pblock != NULL)
	{
		delete m_pblock;
	}
}


bool base_tetrix_scene::CreateScene( int iwidth, int ilength )
{
	m_pcontext_activity = CreateSceneContext( 2, iwidth, ilength );

	if(m_pcontext_activity == NULL)
	{
		return false;
	}

	m_pcontext_freeze = CreateSceneContext( 2, iwidth, ilength );
	
	if(m_pcontext_activity == NULL)
	{
		return false;
	}

	m_pblock = new base_block;

	return true;
}

void base_tetrix_scene::DestroyScene()
{	
	if(m_pcontext_freeze != NULL)
	{
		DestroySceneContext(m_pcontext_freeze);
		m_pcontext_freeze = NULL;
	}

	if(m_pcontext_activity != NULL)
	{
		DestroySceneContext(m_pcontext_activity);
		m_pcontext_activity = NULL;
	}
}

void base_tetrix_scene::StartGame()
{
	ClearSceneContext(m_pcontext_freeze);
	ClearSceneContext(m_pcontext_activity);

	unsigned int iBlock_index = GenerateRandomNumber( 0, 4);

	m_pblock->initblock(m_pcontext_freeze->pSceneData, 
		                m_pcontext_freeze->b_x_size,
						m_pcontext_freeze->b_y_size,
						(block_category)iBlock_index);
	m_pblock->draw(m_pcontext_activity);

}
	
void base_tetrix_scene::EndGame()
{
	
}
	
void base_tetrix_scene::user_right()
{
	m_pblock->move_right();
	DrawBlock();
}
	
void base_tetrix_scene::user_left()
{
	m_pblock->move_left();
	DrawBlock();
}
	
void base_tetrix_scene::user_fall()
{
	while ( m_pblock->isBlockDown() == 0 )
	{
		m_pblock->fall_slow();
		DrawBlock();
	} 
}
	
void base_tetrix_scene::user_down()
{
	m_pblock->fall_slow();
	DrawBlock();
}

void base_tetrix_scene::user_rotate()
{
	m_pblock->rotate();
	DrawBlock();
}

void base_tetrix_scene::DrawBlock()
{
	Sync_Scene_Data(m_pcontext_activity, m_pcontext_freeze);
	m_pblock->draw(m_pcontext_activity);
}

void base_tetrix_scene::CheckGameStatus()
{
	int i;
	int j;
//firstly,check that is need to clear blocks
	for(i = 0; i < m_pcontext_activity->b_y_size; i++)
		for(j = 0; j < m_pcontext_activity->b_x_size; j++)
		{
			
		}
}