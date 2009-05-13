//Second Foundation Copyright @

#include "stdafx.h"
#include "tetrix_scene.h"

base_tetrix_scene::base_tetrix_scene()
{
	m_pcontext_freeze   = NULL;
	m_pcontext_activity = NULL;
}

base_tetrix_scene::~base_tetrix_scene()
{
	if(m_pcontext_freeze != NULL)
	{
		DestroySceneContext(m_pcontext_freeze);
	}

	if(m_pcontext_activity != NULL)
	{
		DestroySceneContext(m_pcontext_activity);
	}
}


bool base_tetrix_scene::CreateScene( int iwidth, int ilength )
{

}

void base_tetrix_scene::DestroyScene()
{

}

void base_tetrix_scene::StartGame()
{

}
	
void base_tetrix_scene::EndGame();
{

}
	
void base_tetrix_scene::user_right()
{

}
	
void base_tetrix_scene::user_left()
{

}
	
void base_tetrix_scene::user_fall()
{

}
	
void base_tetrix_scene::user_down()
{

}

void base_tetrix_scene::user_rotate()
{

}