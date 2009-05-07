//Second foundation Copyright @

#include "tetrix_context.h"

scene_context * CreateSceneContext( int idimension, int iX, int iY, int iZ )
{
	if(idimension != 2 && idimension != 3 )
	{
		return NULL;
	}

	if(idimension == 3 && iZ == 0 )
	{
		return NULL;
	}

	int idata_size = 0;
	
	scenen_context * pRetContext = (scenen_context *)malloc(sizeof(scenen_context));
	memset(pRetContext, 0, sizeof(scenen_context));

	pRetContext->b_dimension = idimension;

	switch(idimension)
	{
		case 2:
		{
			idata_size = iX*iY;
			pRetContext->b_x_size = (unsigned char)iX;
			pRetContext->b_y_size = (unsigned char)iY;		
		}
		break;
		case 3:
		{
			idata_size = iX*iY*iZ;
			pRetContext->b_x_size = (unsigned char)iX;
			pRetContext->b_y_size = (unsigned char)iY;
			pRetContext->b_z_size = (unsigned char)iZ;
		}
		break;
		/*default:
		{
			return NULL;
		}*/
	}

	pRetContext->pSceneData = (unsigned char*)malloc(idata_size);
	memset(pRetContext->pSceneData, 0, idata_size);

	return pRetContext; 
}


bool Sync_Scene_Data(scene_context *pcontext, unsigned char * pdata)
{
	if( pcontext == NULL || pdata == NULL )
	{
		return false;
	}

	int iSize_data = pcontext->b_x_size*pcontext->b_y_size*((pcontext->b_z_size == 0)? 1:pcontext->b_z_size)

	memcpy(pcontext->pSceneData, pdata, iSize_data);

	return true;
}

void DestroySceneContext(scene_context *pcontext)
{
	if(pcontext != NULL)
	{
		if(pcontext->pSceneDate != NULL)
		{
			free(pcontext->pSceneDate);
			pcontext->pSceneDate = NULL;
		}

		free(pcontext);
		pcontext = NULL;
	}
}
