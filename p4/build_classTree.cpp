#include <stdlib.h>
#include <string>
#include <string.h>
#include <map>
#include <list>
#include <cstdio>
#include "quack.h"
#include <algorithm>

using namespace std;
//extern void yyerror(const char* msg);
extern int error_flag;

// Build Class Hierarchy Tree
// - check duplicate class names
// - check invald class names (Obj, Int, ...)
// - build tree_list
// - add method names to tree_nodes

// external data structures
extern vector < string > class_names;
extern list < tree_node *> *tree_list;

int if_node::build_classTree() {
	if_condition->build_classTree();
	if_body->build_classTree();

	//elseif
	list<r_expr_node *>::const_iterator c_iter;
	list<statement_block_node *>::const_iterator b_iter;

	c_iter = elif_pairs->elif_conditions->begin();
	b_iter = elif_pairs->elif_bodies->begin();

	for (int i = 0; i < elif_pairs->size; i++, c_iter++, b_iter++) {
		(*c_iter)->build_classTree();
		(*b_iter)->build_classTree();
	}

	//else
	if(else_body != NULL)
	{	
		else_body->build_classTree();
	}
}

int while_node::build_classTree() 
{
	condition->build_classTree();
	body->build_classTree();
}

int statement_block_node::build_classTree() 
{
	list<statement_node *>::const_iterator iter;
	for (iter = statements->begin(); iter != statements->end(); ++iter) {
		(*iter)->build_classTree();
	}
}

tree_node * class_sig_node::build_classTree() 
{
	// check if parent class is defined (in the list)
	int flag = 1;
	for(int i=0; i<class_names.size(); i++)
	{
		if(strcmp(parent, class_names[i].c_str() ) == 0 ) flag = 0;
	}

	if (flag)	{
		fprintf(stderr, "error:%d:  parent class %s not defined\n", lineno, parent);
		error();
	}

	//check if class name among default classes
	const char* default_classes[] = { "Obj", "Int", "Nothing", "String", "Boolean" };

	for( int i=0; i<5; i++)
	{
		if(! strcmp( class_name, default_classes[i])) {
			fprintf(stderr, "error:%d: class name %s is a default class\n", lineno, class_name); 
			error();
		}
	}

	//check if class extends itself
	if( strcmp( parent, class_name) == 0) {
		fprintf(stderr, "error:%d: class %s cannot extend %s\n",lineno, class_name,parent);
		error();
	}

	// add class to tree_list
	string p(parent);
	string c(class_name);

	tree_node * new_tree_node = append_tree(tree_list, p, c); //returns new tree node

	if (new_tree_node == NULL) {
		 fprintf(stderr, "error:%d:  ill-defined class hierarchy, %s extends %s\n",
				        lineno, c.c_str(), p.c_str());
		 error();
	   exit(0);
	}

	return new_tree_node;
}

int class_node::build_classTree() 
{
	class_tree_node = sig->build_classTree();

	class_tree_node->AST_node = this;

	body->build_classTree(class_tree_node);
}

tree_node * program_node::build_classTree() 
{

	// add default classes to names list 
	class_names.push_back("Obj");
	class_names.push_back("Int");
	class_names.push_back("String");
	class_names.push_back("Nothing");
	class_names.push_back("Boolean");


	//sorting vector to check for duplicates
	sort( class_names.begin(), class_names.end() );

	for( int i=1; i < class_names.size(); i++ )
	{
		if ( class_names[i].compare(class_names[i-1] ) == 0)
		{
			fprintf(stderr,"error: duplicate class name %s\n", class_names[i].c_str());
			error();
		}
	}

	//adding default tree nodes to tree list
	tree_node *Obj = new tree_node("Obj");
	tree_node *Int = new tree_node("Int");
	tree_node *String = new tree_node("String");
	tree_node *Nothing = new tree_node("Nothing");
	tree_node *Boolean = new tree_node("Boolean");


	// Class node for Obj
//	list<method_node *> *obj_method_list = new list<method_node *>();
//
//	vector <f_arg_pair *> *obj_f_args = new vector <f_arg_pair *>();
//	obj_f_args->push_back( new f_arg_pair("o", "Obj"));
//  
//	obj_method_list->push_back( new method_node("PRINT", 
//								obj_f_args, 
//								"Nothing", 
//							  NULL,	
//								0) );
//	obj_method_list->push_back( new method_node("STR", 
//								obj_f_args, 
//								"String", 
//							  NULL,	
//								0) );
//
//
//	class_node *Obj_class = new class_node(
//		new class_sig_node("Obj", new vector<f_arg_pair *>() , "Obj", 0), 
//		new class_body_node(new list <statement_node *>(), obj_method_list), 
//	  0);
//
//	Obj_class->class_tree_node = Obj;
//	Obj->AST_node = Obj_class;
//
//	class_list->push_back(Obj_class);
																											
	tree_list = new list <tree_node*>();

	tree_list->push_back(Obj);
	tree_list->push_back(Int);
	tree_list->push_back(String);
	tree_list->push_back(Boolean);
	tree_list->push_back(Nothing);

	Obj->children.push_back(Int);
	Obj->children.push_back(String);
	Obj->children.push_back(Nothing);
	Obj->children.push_back(Boolean);

	Obj->method_names.push_back("EQUALS");
	Obj->method_names.push_back("PRINT");
	Obj->method_names.push_back("STR");

	Int->method_names.push_back("PLUS");
	Int->method_names.push_back("MINUS");
	Int->method_names.push_back("TIMES");
	Int->method_names.push_back("DIVIDE");
	Int->method_names.push_back("EQUALS");
	Int->method_names.push_back("ATLEAST");
	Int->method_names.push_back("ATMOST");
	Int->method_names.push_back("LESS");
	Int->method_names.push_back("MORE");

	String->method_names.push_back("ATLEAST");
	String->method_names.push_back("ATMOST");
	String->method_names.push_back("LESS");
	String->method_names.push_back("MORE");

	Int->parent = Obj;
	String->parent = Obj;
	Nothing->parent = Obj;
	Boolean->parent = Obj;

	list<class_node *>::const_iterator c_iter;
	for (c_iter = class_list->begin(); c_iter != class_list->end(); ++c_iter) {
		(*c_iter)->build_classTree();
	}

	list<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_list->begin(); s_iter != statement_list->end(); ++s_iter) {
		(*s_iter)->build_classTree();
	}

	return Obj;

}

int method_node::build_classTree(tree_node * class_tree_node) 
{


	// add method name to appropriate tree_node
	string str_mname(method_name);

	// if method already in class_that_defined_method, throw error

	tree_node *v = class_tree_node;
	if (find(v->method_names.begin(), v->method_names.end(), str_mname) != v->method_names.end())
	{
		fprintf(stderr, "error:%d : Method %s already defined for class %s\n", 
				lineno, str_mname.c_str(), v->name.c_str() );	
		error();
	}
	else {
		class_tree_node->method_names.push_back(str_mname);
	}

	body->build_classTree();

	return 0;
}

int class_body_node::build_classTree(tree_node * class_tree_node)
{
	list<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_list->begin(); s_iter != statement_list->end(); ++s_iter) {
		(*s_iter)->build_classTree();
	}

	list<method_node *>::const_iterator  m_iter;
	for (m_iter = method_list->begin(); m_iter != method_list->end(); ++m_iter) {
		// send appropriate class tree_node 
		(*m_iter)->build_classTree(class_tree_node);
	}

	return 0;
}

int return_node::build_classTree() 
{
	if (return_value != NULL) 
		return_value->build_classTree();

	return 0;
}

int l_expr_node::build_classTree()
{
	if(instance != NULL)
	{
		instance->build_classTree();
	}

	return 0;
}

int assign_node::build_classTree(){
	lhs->build_classTree();
	rhs->build_classTree();

	return 0;
}

int constructor_call_node::build_classTree() 
{
	// if class not in class list print error
	int flag = 1;
	for(int i=0; i<class_names.size(); i++)
	{
		if(strcmp(c_name, class_names[i].c_str() ) == 0 ) flag = 0;
	}

	if (flag) {
		fprintf(stderr,"error: %d:  class %s not defined\n", lineno, c_name);
		error();
	}

	list<r_expr_node *>::const_iterator iter;
	for (iter = arg_list->begin(); iter != arg_list->end(); ++iter) {
		(*iter)->static_checks();
	}

	return 0;
}

int method_call_node::build_classTree() 
{
	instance->build_classTree();

	list<r_expr_node *>::const_iterator iter;
	for (iter = arg_list->begin(); iter != arg_list->end(); ++iter) {
		(*iter)->build_classTree();
	}
}

int unary_node::build_classTree()
{
	right->build_classTree();
}

int plus_node::build_classTree() 
{
	left->build_classTree();
	right->build_classTree();
}

int minus_node::build_classTree() 
{
	left->build_classTree();
	right->build_classTree();
}

int times_node::build_classTree() 
{
	left->build_classTree();
	right->build_classTree();
}

int divide_node::build_classTree() 
{
	left->build_classTree();
	right->build_classTree();
}

int compare_node::build_classTree()
{
	left->build_classTree();
	right->build_classTree();
}

int int_node::build_classTree() 
{

}

int str_node::build_classTree() 
{

}
