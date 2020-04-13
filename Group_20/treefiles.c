#include "astdef.h"
#include "nary_tree.h"
#include "treefiles.h"
int naryTreesize(treenode* root)//returns number of nodes in nary tree 
{
	int num_nodes = 0;
	if(root==NULL)
	{
		return 0;
	}
	if(root!=NULL)
	{
		num_nodes+=1;
		for(int i=0;i<root->n;i++)
		{
			num_nodes+=naryTreesize(root->children[i]);
		}
	}
	return num_nodes;
}

int ASTsize(astnode* root)
{
	int num_nodes = 0;
	if(root==NULL)
	{
		return 0;
	}
	if(root!=NULL)
	{
		num_nodes+=1;
		for(int i=0;i<root->n;i++)
		{
			num_nodes+=ASTsize(root->children[i]);
		}
	}
	return num_nodes;
}
