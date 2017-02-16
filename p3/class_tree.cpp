#include <string>
#include <string.h>
#include <cstdio>
#include <list>
#include "class_tree.h"
using namespace std;

int print_tree (tree_node *root, int level) {
	printf("%*s\n", level + ( int ) (root->name).length(), root->name.c_str());
	for(int i=0; i<root->children.size(); i++)
	{ 
		print_tree(root->children[i], level + 2 );
	}
} 

void append_tree( list <tree_node *> *tree_list, string parent_class, string new_class)
{
  
  // get new tree node
  tree_node *new_tree_node = NULL;
  tree_node *parent_tree_node = NULL;

  list<tree_node *>::const_iterator iter;
  for (iter = tree_list->begin(); iter != tree_list->end(); ++iter) {
    if ( (*iter)->name.compare(new_class) == 0 ) new_tree_node = (*iter);
    if ( (*iter)->name.compare(parent_class) == 0 ) parent_tree_node = (*iter);
  }

  // case 1
  if (new_tree_node == NULL && parent_tree_node == NULL) {
    //printf("CASE 1, new: %s, parent:%s\n", new_class.c_str(), parent_class.c_str());
    
    new_tree_node = new tree_node(new_class);
    parent_tree_node = new tree_node(parent_class);

    new_tree_node->parent = parent_tree_node;
    parent_tree_node->children.push_back(new_tree_node);

    tree_list->push_back(new_tree_node);
    tree_list->push_back(parent_tree_node);
  }

  // case 2
  else if (new_tree_node == NULL && parent_tree_node != NULL ) {
    //printf("CASE 2, new: %s, parent:%s\n", new_class.c_str(), parent_class.c_str());

    new_tree_node = new tree_node(new_class);
    
    new_tree_node->parent = parent_tree_node;
    parent_tree_node->children.push_back(new_tree_node);

    tree_list->push_back(new_tree_node);
  }

  // case 3
  else if (new_tree_node != NULL && parent_tree_node == NULL) {
    //printf("CASE 3, new: %s, parent:%s\n", new_class.c_str(), parent_class.c_str());
    
    parent_tree_node = new tree_node(parent_class);

    new_tree_node->parent = parent_tree_node;
    parent_tree_node->children.push_back(new_tree_node);
    
    tree_list->push_back(parent_tree_node);
  }

  // case 4
  else if (new_tree_node != NULL && parent_tree_node != NULL ) {
    //printf("CASE 4, new: %s, parent:%s\n", new_class.c_str(), parent_class.c_str());
    fprintf(stderr, "error: ill-defined class hierarchy, %s extends %s\n", 
        new_class.c_str(), parent_class.c_str());
  }
        
}
