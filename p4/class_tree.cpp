#include <string>
#include <string.h>
#include <cstdio>
#include <list>
#include "class_tree.h"
#include <cstdlib>
using namespace std;

int print_tree (tree_node *root, int level) {
 	
 	if (root == NULL) {
		printf("print_tree: Root is NULL\n");
		exit(0);
	}
      
	printf("%*s%s\n", level, "", root->name.c_str());

        for (int i=0; i < root->method_names.size(); i++) {
          printf("%*s[%s]\n", level + 1, "", root->method_names[i].c_str());
        }
        

	for(int i=0; i<root->children.size(); i++)
	{ 
		print_tree(root->children[i], level + 2 );
	}
} 

tree_node * append_tree( list <tree_node *> *tree_list, string parent_class, string new_class)
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
	//exit(0);
  }
  return new_tree_node;        
}

//get the tree node matching the class name
tree_node * get_tree_node(list < tree_node *> *tree_node_list, string cname)
{
	list<tree_node *>::const_iterator iter;
	for (iter = tree_node_list->begin(); iter != tree_node_list->end(); ++iter) {
		if ( (*iter)->name.compare(cname) == 0 ) return (*iter);
	}
	fprintf(stderr,"error : class name \"%s\" not in tree list\n",cname.c_str() );

}


// check to see if a class defines a method
int class_defines_method(tree_node * class_node, string method_name) 
{
  for (int i = 0; i < class_node->method_names.size(); i++) {
    if (class_node->method_names[i].compare(method_name) == 0) return 1;
  }

  return 0;
}



