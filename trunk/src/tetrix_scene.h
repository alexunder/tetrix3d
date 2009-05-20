//Second Foundation Copyright @

#ifndef _TETRIX_SCENE
#define _TETRIX_SCENE

#include "tetrix_context.h"
#include "tetrix_block.h"

typedef void (*gameovercallback)(void);

class base_tetrix_scene
{
public:
	base_tetrix_scene();
	~base_tetrix_scene();

	bool CreateScene(int iwidth, int ilength, gameovercallback pfncallback);
	void DestroyScene();

	void StartGame(); 
	void EndGame();

	void user_right();
	void user_left();
	void user_fall();
	void user_down();
	void user_rotate();

	bool isOneGridNeedShow( int index )
	{
		return (m_pcontext_activity->pSceneData[index] != 0);
	}
private:
	void DrawBlock();
	void CheckGameStatus();
	void BlockFactory();
private:
	scene_context * m_pcontext_freeze;
	scene_context * m_pcontext_activity;
	base_block * m_pblock;
	gameovercallback m_pfngameover;
};

#endif
