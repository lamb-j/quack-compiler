#include <string>
#include <string.h>
#include <cstdio>
#include "class_tree.h"
using namespace std;

int print_tree (tree_node *root, int level) {
	printf("%*s\n", level + ( int ) (root->name).length(), root->name.c_str());
	for(int i=0; i<root->children.size(); i++)
	{ 
		print_tree(root->children[i], level + 2 );
	}
} 

/*
void append_tree(tree *parent, string c_name)
{
	if(
}
*/

