/////////////////////////////////////////////////////////////////////////////
// 
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//  
//  Use of this source code is subject to the terms of the Microsoft shared
//  source or premium shared source license agreement under which you licensed
//  this source code. If you did not accept the terms of the license agreement,
//  you are not authorized to use this source code. For the terms of the license,
//  please see the license agreement between you and Microsoft or, if applicable,
//  see the SOURCE.RTF on your install media or the root of your tools installation.
//  THE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES. 
//
//  Module Name:
//
//      main.cpp
//
//  Abstract:
//
//      a simple test for the nlsapi:LocaleNameToLCID 
//  
//  Author:
//
//      Chenyu Xu 17-Mar-2009
//
//  Environment:
//
//      Win32
//  
//  Notes:
//  
//      NLS API simple test code.
//
//  Revision History:
//
//      13-Mar-2009 Chenyu,xu Initialization        
//
/////////////////////////////////////////////////////////////////////////////

#include "windows.h"
#include "stdio.h"

void base_matrix_rotate_90_ckw( int * pMatrix, int dim )
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

int _cdecl main(
    int argc,
    char *argv[])
{
	int a[100] = {0};

	int i;

	for(i = 0; i < 100; i ++)
	{
		a[i] = i+1;
	}

	int dim = 10;

	printf("the orignal matrix is:\n");

	for(i = 0; i < dim*dim; i++ )
	{
		printf("%3d ", a[i] );

		if( (i+1)%dim == 0 )
		{
			printf("\n");
		}
	}

    base_matrix_rotate_90_ckw( a, dim );

	printf("the rotated matrix is:\n");

	for(i = 0; i < dim*dim; i++ )
	{
		printf("%2d ", a[i] );

		if( (i+1)%dim == 0 )
		{
			printf("\n");
		}
	}
}

/* This code example produces the following output:

Locale Name for 0x10407 is de-DE_phoneb
LCID for de-DE_phoneb is 0x10407

*/
		//printf("the rotating matrix is:\n");

		//for(int index = 0; index < dim*dim; index++ )
		//{
		//	printf("%2d ", pMatrix[index] );

		//	if( (index+1)%dim == 0 )
		//	{
		//		printf("\n");
		//	}
		//}