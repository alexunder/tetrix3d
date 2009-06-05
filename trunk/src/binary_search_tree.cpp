//Foundation Research @

#include "binary_search_tree.h"


bool create_null_bin_tree(bin_tree ** ptree)
{
	if(ptree == NULL)
	{
		return false;
	}

	ptree = (bin_tree*)malloc(sizeof(bin_tree));

	memset(ptree, 0, sizeof(bin_tree));

	return true;
}

void destroy_bin_tree(bin_tree * ptree)
{
	
	if(ptree != NULL)
	{
		//in this place , i will delete all nodes
		//
		free(ptree);
		ptree = NULL;
	}
}

void insert_bin_tree_node(bin_tree * ptree, int value)
{
	if(ptree == NULL)
	{
		return;
	}

	bin_tree_node * pnew_node = (bin_tree_node *)malloc(sizeof(bin_tree_node));
	pnew_node->ikeyvalue = value;

	if(ptree->proot == NULL)
	{
		ptree->proot = pnew_node;
		return;
	}

	bin_tree_node * pcurrentnode = ptree->proot;
	bin_tree_node * ptempnode = NULL;

	while(pcurrentnode != NULL)
	{
		ptempnode = pcurrentnode;

		if(value < pcurrentnode->ikeyvalue)
		{
			pcurrentnode = pcurrentnode->pleftchild;
		}
		else
		{
			pcurrentnode = pcurrentnode->prightchild;
		}
	}

	pnew_node->pparent = ptempnode;

	if(pnew_node->ikeyvalue < ptempnode->ikeyvalue)
	{
		ptempnode->pleftchild = pnew_node;
	}
	else
	{
		ptempnode->prightchild = pnew_node;
	}

	return;
}

bool delete_bin_tree_node(bin_tree * ptree, int value)
{
	if(ptree == NULL)
	{
		return false;
	}

	tree_node * pNode = search_bin_tree_node(ptree, value);

	if(pNode == NULL)
	{
		return false; 
	}


}

tree_node * search_bin_tree_node(bin_tree * ptree, int value)
{
	if(ptree == NULL)
	{
		return NULL;
	}

	tree_node * pNode_iterator = ptree->proot;

	while( (pNode_iterator != NULL) && (pNode_iterator->ikeyvalue != value) )
	{
		if(value < pNode_iterator->ikeyvalue)
		{
			pNode_iterator = pNode_iterator->ileftchild; 
		}
		else
		{
			pNode_iterator = pNode_iterator->irightchild;
		}
	}

	return pNode_iterator;
}
