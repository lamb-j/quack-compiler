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
	return 0;	
}

int while_node::build_classTree() 
{
	condition->build_classTree();
	body->build_classTree();
	return 0;	
}

int statement_block_node::build_classTree() 
{
	list<statement_node *>::const_iterator iter;
	for (iter = statements->begin(); iter != statements->end(); ++iter) {
		(*iter)->build_classTree();
	}
	return 0;	
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
	return 0;	
}

tree_node * program_node::build_classTree() 
{
	// add default classes to names list 
	class_names.push_back("");
	class_names.push_back("Obj");
	class_names.push_back("Int");
	class_names.push_back("String");
	class_names.push_back("Nothing");
	class_names.push_back("Boolean");
	//class_names.push_back("Dummy");


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

	// Class node for Obj
	list<method_node *> *obj_method_list = new list<method_node *>();

	//Arguments for Obj methods

	vector <f_arg_pair *> *obj_f_args = new vector <f_arg_pair *>();
	//obj_f_args->push_back( new f_arg_pair("o", "Obj"));
	//Method of Obj class
	obj_method_list->push_back( new method_node("PRINT", 
				obj_f_args, 
				"Nothing", 
				new statement_block_node( new list<statement_node*>()),	
				0) );
	obj_method_list->push_back( new method_node("STR", 
				obj_f_args, 
				"String", 
				new statement_block_node( new list<statement_node*>()),	
				0) );

	obj_method_list->push_back( new method_node("EQ", 
				obj_f_args, 
				"Boolean", 
				new statement_block_node( new list<statement_node*>()),	
				0) );

	class_node *Obj_class = new class_node(
			new class_sig_node("Obj", new vector<f_arg_pair *>() , "", 0), 
			new class_body_node(new list <statement_node *>(), obj_method_list), 
			0);


	class_list->push_back(Obj_class);

	// Class node for Nothing
	list<method_node *> *nothing_method_list = new list<method_node *>();

	class_node *Nothing_class = new class_node(
			new class_sig_node("Nothing", new vector<f_arg_pair *>() , "Obj", 0), 
			new class_body_node(new list <statement_node *>(), nothing_method_list), 
			0);

	class_list->push_back(Nothing_class);

	// Class node for Integer 
	list<method_node *> *integer_method_list = new list<method_node *>();
	//Add integer methods: plus, minus, divide, times, less, more, atleast, atmost, equals

	vector <f_arg_pair *> *integer_f_args = new vector <f_arg_pair *>();
	integer_f_args->push_back( new f_arg_pair("x", "Int"));
	integer_f_args->push_back( new f_arg_pair("y", "Int"));

	integer_method_list->push_back( new method_node("PLUS", 
				integer_f_args, 
				"Int", 
				new statement_block_node( new list<statement_node*>()),	
				0) );

	integer_method_list->push_back( new method_node("MINUS", 
				integer_f_args, 
				"Int", 
				new statement_block_node( new list<statement_node*>()),	
				0) );

	integer_method_list->push_back( new method_node("TIMES", 
				integer_f_args, 
				"Int", 
				new statement_block_node( new list<statement_node*>()),	
				0) );

	integer_method_list->push_back( new method_node("DIVIDE", 
				integer_f_args, 
				"Int", 
				new statement_block_node( new list<statement_node*>()),	
				0) );

	integer_method_list->push_back( new method_node("ATMOST", 
				integer_f_args, 
				"Boolean", 
				new statement_block_node( new list<statement_node*>()),	
				0) );

	integer_method_list->push_back( new method_node("ATLEAST", 
				integer_f_args, 
				"Boolean", 
				new statement_block_node( new list<statement_node*>()),	
				0) );

	integer_method_list->push_back( new method_node("LESS", 
				integer_f_args, 
				"Boolean", 
				new statement_block_node( new list<statement_node*>()),	
				0) );

	integer_method_list->push_back( new method_node("MORE", 
				integer_f_args, 
				"Boolean", 
				new statement_block_node( new list<statement_node*>()),	
				0) );

	integer_method_list->push_back( new method_node("EQUALS", 
				integer_f_args, 
				"Boolean", 
				new statement_block_node( new list<statement_node*>()),	
				0) );

	class_node *Integer_class = new class_node(
			new class_sig_node("Int", new vector<f_arg_pair *>() , "Obj", 0), 
			new class_body_node(new list <statement_node *>(), integer_method_list), 
			0);

	class_list->push_back(Integer_class);	

	// Class node for String 
	list<method_node *> *string_method_list = new list<method_node *>();

	vector <f_arg_pair *> *string_f_args = new vector <f_arg_pair *>();
	string_f_args->push_back( new f_arg_pair("other", "String"));

	string_method_list->push_back( new method_node("PLUS", 
				string_f_args, 
				"String", 
				new statement_block_node( new list<statement_node*>()),	
				0) );

	string_method_list->push_back( new method_node("EQUALS", 
				string_f_args, 
				"Boolean", 
				new statement_block_node( new list<statement_node*>()),	
				0) );

	class_node *String_class = new class_node(
			new class_sig_node("String", new vector<f_arg_pair *>() , "Obj", 0), 
			new class_body_node(new list <statement_node *>(), string_method_list), 
			0);

	class_list->push_back(String_class);

	// Class node for Boolean
	list<method_node *> *boolean_method_list = new list<method_node *>();

	vector <f_arg_pair *> *boolean_f_args = new vector <f_arg_pair *>();
	boolean_f_args->push_back( new f_arg_pair("other", "Boolean"));

	boolean_method_list->push_back( new method_node("EQUALS", 
				boolean_f_args, 
				"Boolean", 
				new statement_block_node( new list<statement_node*>()),	
				0) );

	boolean_method_list->push_back( new method_node("OR", 
				boolean_f_args, 
				"Boolean", 
				new statement_block_node( new list<statement_node*>()),	
				0) );

	boolean_method_list->push_back( new method_node("AND", 
				boolean_f_args, 
				"Boolean", 
				new statement_block_node( new list<statement_node*>()),	
				0) );

	boolean_method_list->push_back( new method_node("NOT", 
				boolean_f_args, 
				"Boolean", 
				new statement_block_node( new list<statement_node*>()),	
				0) );

	class_node *Boolean_class = new class_node(
			new class_sig_node("Boolean", new vector<f_arg_pair *>() , "Obj", 0), 
			new class_body_node(new list <statement_node *>(), boolean_method_list), 
			0);

	class_list->push_back(Boolean_class);
	tree_list = new list <tree_node*>();

	list<class_node *>::const_iterator c_iter;
	for (c_iter = class_list->begin(); c_iter != class_list->end(); ++c_iter) {
		(*c_iter)->build_classTree();
	}

	list<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_list->begin(); s_iter != statement_list->end(); ++s_iter) {
		(*s_iter)->build_classTree();
	}

	return Obj_class->class_tree_node;

	return 0;	
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
	else
	{
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

	if (flag)
	{
		fprintf(stderr,"error: %d:  class %s not defined\n", lineno, c_name);
		error();
	}

	list<r_expr_node *>::const_iterator iter;
	for (iter = arg_list->begin(); iter != arg_list->end(); ++iter)
	{
		(*iter)->build_classTree();
	}

	return 0;
}

int method_call_node::build_classTree() 
{
	instance->build_classTree();

	list<r_expr_node *>::const_iterator iter;
	for (iter = arg_list->begin(); iter != arg_list->end(); ++iter)
	{
		(*iter)->build_classTree();
	}
	return 0;	
}

int int_node::build_classTree() 
{

	return 0;	
}

int str_node::build_classTree() 
{

	return 0;	
}
