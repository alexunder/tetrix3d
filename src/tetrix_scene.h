//Second Foundation Copyright @

#ifndef _TETRIX_SCENE
#define _TETRIX_SCENE

#include "tetrix_context.h"
#include "tetrix_block.h"

class base_tetrix_scene
{
public:
	base_tetrix_scene();
	~base_tetrix_scene();

	bool CreateScene();
	void DestroyScene();

	void StartGame();
	void EndGame();

	void user_right();
	void user_left();
	void user_fall();
	void user_down();
	void user_rotate();

private:
	scene_context * m_pcontext_freeze;
	scene_context * m_pcontext_activity;
	base_block * m_pblock;
};

#endif
