#include <string>
#include <string.h>
#include <cstdio>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include "quack.h"
#include <cstdlib>

//class_tree
//- class tree (class hierarchy related functions

using namespace std;
extern vector <tree_node *> *tree_vector;

void codegen_class(tree_node *root) {

	root->AST_node->codegen();

	for(int i = 0; i< root->children.size(); i++) {
		codegen_class(root->children[i]);
	}
}

void type_check_class(tree_node *root) {

	root->AST_node->type_checks(NULL, NULL);

	for(int i = 0; i< root->children.size(); i++) {
		type_check_class(root->children[i]);
	}
}
  
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
	return 0;
} 

tree_node * append_tree( vector <tree_node *> *tree_vector, string parent_class, string new_class)
{
  
  // get new tree node
  tree_node *new_tree_node = NULL;
  tree_node *parent_tree_node = NULL;

  vector<tree_node *>::const_iterator iter;
  for (iter = tree_vector->begin(); iter != tree_vector->end(); ++iter) {
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

    tree_vector->push_back(new_tree_node);
    tree_vector->push_back(parent_tree_node);
    return new_tree_node;
  }

  // case 2
  if (new_tree_node == NULL && parent_tree_node != NULL ) {
    //printf("CASE 2, new: %s, parent:%s\n", new_class.c_str(), parent_class.c_str());

    new_tree_node = new tree_node(new_class);
    
    new_tree_node->parent = parent_tree_node;
    parent_tree_node->children.push_back(new_tree_node);

    tree_vector->push_back(new_tree_node);
		return new_tree_node;
  }

  // case 3
  if (new_tree_node != NULL && parent_tree_node == NULL) {
    //printf("CASE 3, new: %s, parent:%s\n", new_class.c_str(), parent_class.c_str());
    
    parent_tree_node = new tree_node(parent_class);

    new_tree_node->parent = parent_tree_node;
    parent_tree_node->children.push_back(new_tree_node);
    
    tree_vector->push_back(parent_tree_node);
		return new_tree_node;
  }

  // case 4
  if (new_tree_node != NULL && parent_tree_node != NULL ) {
    //printf("CASE 4, new: %s, parent:%s\n", new_class.c_str(), parent_class.c_str());
			new_tree_node->parent = parent_tree_node;
			parent_tree_node->children.push_back(new_tree_node);

			return new_tree_node;
  }

	printf("ERROR IN APPEND TREE\n");
  return NULL;        
}

//get the tree node matching the class name
tree_node * get_tree_node(vector < tree_node *> *tree_node_vector, string cname)
{
	vector<tree_node *>::const_iterator iter;
	for (iter = tree_node_vector->begin(); iter != tree_node_vector->end(); ++iter) {
		if ( (*iter)->name.compare(cname) == 0 ) return (*iter);
	}
	fprintf(stderr,"error : class name \"%s\" not in tree vector\n",cname.c_str() );
	exit(0);

}

// check to see if a class defines a method
int class_defines_method(tree_node * class_node, string method_name) 
{
  for (int i = 0; i < class_node->method_names.size(); i++)
	{
    if (class_node->method_names[i].compare(method_name) == 0) return 1;
  }

  return 0;
}

string least_common_ancestor(string A, string B)
{

  if (!A.compare("Dummy")) return B;
  if (!B.compare("Dummy")) return A;

  string tmp;

  // make parent vector for A
  vector <string> A_vec;
  tmp = A;

  while (tmp.compare("Obj") != 0) {


		if (get_tree_node(tree_vector, tmp)->parent == NULL || find(A_vec.begin(), A_vec.end(), tmp) != A_vec.end() ) {
			return "Disconnected";
		}
   
    A_vec.push_back(tmp);
    tmp = get_tree_node(tree_vector,tmp)->parent->name;
  }

  // make parent vec for B
  vector <string> B_vec;
  tmp = B;

  while (tmp.compare("Obj") != 0) {
    B_vec.push_back(tmp);
    tmp = get_tree_node(tree_vector,tmp)->parent->name;

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

  // If we didn't find an ancestor, return the node with the smaller vector
  return A_vec.size() < B_vec.size() ? A : B;
}


class_node * get_AST_class_node(string class_name) {

	tree_node * class_tree_node = get_tree_node(tree_vector, class_name);

	return class_tree_node->AST_node;
}

method_node * get_AST_method_node(string class_name, string method_name) {

	vector<method_node *> *method_vector  = (get_AST_class_node(class_name))->body->method_vector;

	vector <method_node *>::const_iterator iter;
	for (iter = method_vector->begin(); iter != method_vector->end(); ++iter) {
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

void add_parent_methods(vector <method_node *> *parent_mvector, vector <method_node *> *child_mvector, string child_class)
{
	vector<method_node*>::const_iterator pvector_iter;
	vector<method_node*>::const_iterator cvector_iter;
	for(pvector_iter = parent_mvector->begin(); pvector_iter != parent_mvector->end(); ++pvector_iter)
	{
		int pflag = 0;
		const char* p_mname = (*pvector_iter)->method_name;
		const char* p_mtype = (*pvector_iter)->return_type;

		for(cvector_iter = child_mvector->begin(); cvector_iter != child_mvector->end(); ++cvector_iter)
		{
			const char* c_mname = (*cvector_iter)->method_name;
			const char* c_mtype = (*cvector_iter)->return_type;
			
			if( strcmp(p_mname, c_mname) == 0)
			{

				pflag = 1;
				//since pname = cname: check for overriding methods
				if(!is_subclass(c_mtype,p_mtype))
				{
					fprintf(stderr,"error:%d: return type \"%s\" for method \"%s\" in subclass"
							" \"%s\" is not subtype of overriden method \n",
							(*cvector_iter)->lineno, c_mtype, c_mname, child_class.c_str() );
					error();
				}

				//check number of args for each method
				if((*pvector_iter)->formal_args->size() != (*cvector_iter)->formal_args->size() )
				{
					fprintf(stderr,"error:%d: formal arg vector size for method %s"
							" in subclass \"%s\" does not match superclass\n",
							(*cvector_iter)->lineno, c_mname, child_class.c_str() );
					error();
				}
				//check type of each arg in overriding method against parent method
				else
				{
					//iterate over both child and parent method arg vector
					vector<f_arg_pair*>::const_iterator p_f_arg_iter;
					vector<f_arg_pair*>::const_iterator c_f_arg_iter;

					vector <f_arg_pair*> *p_arg_vec = (*pvector_iter)->formal_args;
					vector <f_arg_pair*> *c_arg_vec = (*cvector_iter)->formal_args;

					for(int i=0; i < p_arg_vec->size(); i++)
					{
						if(! is_subclass( (*p_arg_vec)[i]->return_type , (*c_arg_vec)[i]->return_type ) )
						{
							fprintf(stderr,"error:%d: argument %d of type %s in method \"%s\""
									" of subclass \"%s\" "
									" is not a supertype of overridden method argument type %s\n",
									(*cvector_iter)->lineno,
									(int) p_arg_vec->size() - 1 - i,
									(*c_arg_vec)[i]->return_type,
									c_mname,
									child_class.c_str(),
									(*p_arg_vec)[i]->return_type);

							error();
						}
					}
				}
				break;
			}
		}

		// Add parent's method to child
		if (!pflag)
		{
				child_mvector->push_back( (*pvector_iter) );
				tree_node * child_tree_node = get_tree_node(tree_vector, child_class);
				child_tree_node->method_names.push_back( string(p_mname) );
		}

	}
}

void add_parent_fields( map <string, string> *parent_fields, map <string, string> *child_fields)
{
	
	map<string, string>::iterator c_fields_iter;
	map<string, string>::iterator p_fields_iter;

	string p_fname, p_ftype;
	string c_fname, c_ftype;

	
	//if parent has no fields, return to class_node
	if(parent_fields->empty())
		return;
	
	for(p_fields_iter = parent_fields->begin(); p_fields_iter != parent_fields->end(); ++p_fields_iter)
	{
		string p_fname = string(p_fields_iter->first);
		string p_ftype = string(p_fields_iter->second);
			
		//if p_fname exist in child_field :  type must match
		//else add to child_field
		if( child_fields->find(p_fname) != child_fields->end() ) 
		{
			//string c_fname = c_fields_iter->first;
			string c_ftype = (*child_fields)[p_fname];
			if( c_ftype.compare(p_ftype) != 0  ) //type not same
			{
				fprintf(stderr,"error: field member \"%s\" of type \"%s\" must match superclass' field type \"%s\"\n",
							p_fname.c_str(), c_ftype.c_str(), p_ftype.c_str()) ;
				error();
			}
		}
		else
		{
			fprintf(stderr,"error: subclass must have field \"%s\" from superclass\n",p_fname.c_str());
			error();
		}
	}
} 

void check_class_tree_hierarchy() {

	vector <tree_node *>::const_iterator iter;

	for (iter = tree_vector->begin(); iter != tree_vector->end(); ++iter) {
    if ( (*iter)->name.compare("") && !is_subclass( (*iter)->name, "Obj") ) {
			fprintf(stderr, "error: ill-defined class hierarchy, see class %s\n", (*iter)->name.c_str());
			error();
		}
	}
}
