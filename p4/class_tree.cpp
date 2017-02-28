#include <string>
#include <string.h>
#include <cstdio>
#include <unistd.h>
#include <list>
#include <algorithm>
#include "quack.h"
#include <cstdlib>

//class_tree
//- class tree (class hierarchy related functions

using namespace std;
extern list <tree_node *> *tree_list;

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
		return new_tree_node;
  }

  // case 2
  if (new_tree_node == NULL && parent_tree_node != NULL ) {
    //printf("CASE 2, new: %s, parent:%s\n", new_class.c_str(), parent_class.c_str());

    new_tree_node = new tree_node(new_class);
    
    new_tree_node->parent = parent_tree_node;
    parent_tree_node->children.push_back(new_tree_node);

    tree_list->push_back(new_tree_node);
		return new_tree_node;
  }

  // case 3
  if (new_tree_node != NULL && parent_tree_node == NULL) {
    //printf("CASE 3, new: %s, parent:%s\n", new_class.c_str(), parent_class.c_str());
    
    parent_tree_node = new tree_node(parent_class);

    new_tree_node->parent = parent_tree_node;
    parent_tree_node->children.push_back(new_tree_node);
    
    tree_list->push_back(parent_tree_node);
		return new_tree_node;
  }

  // case 4
  if (new_tree_node != NULL && parent_tree_node != NULL ) {
    //printf("CASE 4, new: %s, parent:%s\n", new_class.c_str(), parent_class.c_str());
   
		//check if class name among default classes
		  const char* default_classes[] = { "Obj", "Int", "Nothing", "String", "Boolean" };

		int flag = 0;
		for( int i=0; i<5; i++)
	  {
			if ( parent_tree_node->name.compare( string(default_classes[i]) ) == 0 )
				flag = 1;
		} 
		
		if (flag)
		{
			new_tree_node->parent = parent_tree_node;
			parent_tree_node->children.push_back(new_tree_node);

			return new_tree_node;
		}

		error();
		return NULL;
  }

	printf("ERROR IN APPEND TREE\n");
  return NULL;        
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

tree_node * least_common_ancestor(tree_node *A, tree_node *B)
{

  tree_node *tmp;

  // make parent list for A
  vector <tree_node *> A_vec;
  tmp = A;

  while (tmp->name.compare("Obj") != 0) {
    A_vec.push_back(tmp);

    tmp = tmp->parent;
  }

  // make parent vec for B
  vector <tree_node *> B_vec;
  tmp = B;

  while (tmp->name.compare("Obj") != 0) {
    B_vec.push_back(tmp);

    tmp = tmp ->parent;
  }

  // Add Obj
  A_vec.push_back(tmp);
  B_vec.push_back(tmp);

  // compare vecs
  reverse(A_vec.begin(), A_vec.end());
  reverse(B_vec.begin(), B_vec.end());

  int len = min (A_vec.size(), B_vec.size());

  for (int i = 0; i < len; i++) {
    if (A_vec[i] != B_vec[i]) return A_vec[i - 1];
  }

  // If we didn't find an ancestor, return the node with the smaller list
  return A_vec.size() < B_vec.size() ? A : B;
}


string least_common_ancestor(string A, string B)
{

  string tmp;

  // make parent list for A
  vector <string> A_vec;
  tmp = A;

  while (tmp.compare("Obj") != 0) {
    A_vec.push_back(tmp);
   
    tmp = get_tree_node(tree_list,tmp)->parent->name;
  }

  // make parent vec for B
  vector <string> B_vec;
  tmp = B;

  while (tmp.compare("Obj") != 0) {
    B_vec.push_back(tmp);
    tmp = get_tree_node(tree_list,tmp)->parent->name;

  }

  // Add Obj
  A_vec.push_back(tmp);
  B_vec.push_back(tmp);

  // compare vecs
  reverse(A_vec.begin(), A_vec.end());
  reverse(B_vec.begin(), B_vec.end());

  int len = min (A_vec.size(), B_vec.size());

  for (int i = 0; i < len; i++) {
    if ( A_vec[i].compare( B_vec[i] ) !=0 ) 
    {
	return A_vec[i - 1];
    }
  }

  // If we didn't find an ancestor, return the node with the smaller list
  return A_vec.size() < B_vec.size() ? A : B;
}


class_node * get_AST_class_node(string class_name) {

	tree_node * class_tree_node = get_tree_node(tree_list, class_name);

	return class_tree_node->AST_node;
}

method_node * get_AST_method_node(string class_name, string method_name) {

	list<method_node *> *method_list  = (get_AST_class_node(class_name))->body->method_list;

	list <method_node *>::const_iterator iter;
	for (iter = method_list->begin(); iter != method_list->end(); ++iter) {
		if ( strcmp( (*iter)->method_name , method_name.c_str() ) == 0) return (*iter);
	}

	return NULL;

	//fprintf(stderr, "error:%d: Method %s not found in class %s\n", lineno, method_name.c_str(), class_name.c_str());
}

int is_subclass(string sub_class, string super_class)
{
	string lca = least_common_ancestor(sub_class, super_class);
	if(lca.compare(super_class) == 0 )
		return 1;
	else
		return 0;
}

int is_superclass(string super_class, string sub_class)
{ 
  return is_subclass(sub_class, super_class);
}

void add_parent_methods(list <method_node *> *parent_mlist, list <method_node *> *child_mlist)
{
	list<method_node*>::const_iterator plist_iter;
	list<method_node*>::const_iterator clist_iter;
	for(plist_iter = parent_mlist->begin(); plist_iter != parent_mlist->end(); ++plist_iter)
	{
		int pflag = 0;
		const char* pname = (*plist_iter)->method_name;
		const char* ptype = (*plist_iter)->return_type;

		for(clist_iter = child_mlist->begin(); clist_iter != child_mlist->end(); ++clist_iter)
		{
			const char* cname = (*clist_iter)->method_name;
			const char* ctype = (*clist_iter)->return_type;
			
			if( strcmp(pname, cname) == 0)
			{
				pflag = 1;
				//over-riding methods
				if(!is_subclass(ctype,ptype))
				{
					fprintf(stderr,"error:%d: return type %s for method %s does not match\
							its superclasses' method (at %d)\n", (*clist_iter)->lineno, ctype, cname, (*plist_iter)->lineno);  
				}
				//check number of args for each method
				else if((*plist_iter)->formal_args->size() != (*clist_iter)->formal_args->size() )
				{
					fprintf(stderr,"error:%d: formal arg list for method %s does not match\
							superclasses\n",(*clist_iter)->lineno, cname);
				}
			}
			if(!pflag)
			{
				child_mlist->push_back( (*plist_iter) );
			}
		}
	}

}
