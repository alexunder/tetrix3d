//Foundation Research @

#ifndef __H_BINARY_SEARCH_TREE
#define __H_BINARY_SEARCH_TREE

typedef struct _bin_tree_node
{
	int ikeyvalue;
	_bin_tree_node * pparent;
	_bin_tree_node * pleftchild;
	_bin_tree_node * prightchild;
} bin_tree_node;

typedef struct _bin_tree
{
	_bin_tree_node * proot;
	int inum;
} bin_tree;

bool create_null_bin_tree(bin_tree ** ptree);

void destroy_bin_tree(bin_tree * ptree);

void insert_bin_tree_node(bin_tree * ptree, int value);

bool delete_bin_tree_node(bin_tree * ptree, int value);

bool search_bin_tree_node(bin_tree * ptree, int value);
#endif //__H_BINARY_SEARCH_TREE
