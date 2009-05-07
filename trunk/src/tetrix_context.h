//Second Foundation Copyright @

#ifndef _H_TETRIX_CONTEX
#define _H_TETRIX_CONTEX

typedef struct _scene_context
{
	unsigned char   b_dimension;
	unsigned char   b_x_size;
	unsigned char   b_y_size;
	unsigned char   b_z_size;
	unsigned char * pSceneData;
}scene_context;

scene_context * CreateSceneContext( int idimension, int iX, int iY, int iZ );

bool Sync_Scene_Data(scene_context *pcontext, unsigned char * pdata);

vois DestroySceneContext(scene_context *pcontext);

#endif
