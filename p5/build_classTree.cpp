#include <stdlib.h>
#include <string>
#include <string.h>
#include <map>
#include <vector>
#include <cstdio>
#include "quack.h"
#include <algorithm>

using namespace std;

// Build Class Hierarchy Tree
// - check duplicate class names
// - check invald class names (Obj, Int, ...)
// - build tree_vector
// - add method names to tree_nodes

// external data structures
extern vector < string > class_names;
extern vector < tree_node *> *tree_vector;
extern int error_flag;

int if_node::build_classTree() {
	if_condition->build_classTree();
	if_body->build_classTree();

	//elseif
	vector<r_expr_node *>::const_iterator c_iter;
	vector<statement_block_node *>::const_iterator b_iter;

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
	vector<statement_node *>::const_iterator iter;
	for (iter = statements->begin(); iter != statements->end(); ++iter) {
		(*iter)->build_classTree();
	}
	return 0;	
}

tree_node * class_sig_node::build_classTree() 
{
	// check if parent class is defined (in the vector)
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

	// add class to tree_vector
	string p(parent);
	string c(class_name);

	tree_node * new_tree_node = append_tree(tree_vector, p, c); //returns new tree node

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
	// add default classes to names vector 
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
	vector<method_node *> *obj_method_vector = new vector<method_node *>();

	//Arguments for Obj methods
	vector <f_arg_pair *> *obj_f_args = new vector <f_arg_pair *>();

	//Method of Obj class
//	obj_method_vector->push_back( new method_node("PRINT", 
//				obj_f_args, 
//				"Nothing", 
//				new statement_block_node( new vector<statement_node*>()),	
//				0) );
//	obj_method_vector->push_back( new method_node("STR", 
//				obj_f_args, 
//				"String", 
//				new statement_block_node( new vector<statement_node*>()),	
//				0) );
//
//	obj_method_vector->push_back( new method_node("EQ", 
//				obj_f_args, 
//				"Boolean", 
//				new statement_block_node( new vector<statement_node*>()),	
//				0) );

	class_node *Obj_class = new class_node(
			new class_sig_node("Obj", new vector<f_arg_pair *>() , "", 0), 
			new class_body_node(new vector <statement_node *>(), obj_method_vector), 
			0);


	class_vector->push_back(Obj_class);

	// Class node for Nothing
	vector<method_node *> *nothing_method_vector = new vector<method_node *>();

	class_node *Nothing_class = new class_node(
			new class_sig_node("Nothing", new vector<f_arg_pair *>() , "Obj", 0), 
			new class_body_node(new vector <statement_node *>(), nothing_method_vector), 
			0);

	class_vector->push_back(Nothing_class);

	// Class node for Integer 
	vector<method_node *> *integer_method_vector = new vector<method_node *>();

	vector <f_arg_pair *> *integer_f_args = new vector <f_arg_pair *>();
	integer_f_args->push_back( new f_arg_pair("x", "Int"));
	integer_f_args->push_back( new f_arg_pair("y", "Int"));

	vector <f_arg_pair *> *integer_f_args_print = new vector <f_arg_pair *>();
	integer_f_args_print->push_back( new f_arg_pair("this", "Int"));

	vector <string> int_operators;
	int_operators.push_back("PLUS");
	//int_operators.push_back("MINUS");
	//int_operators.push_back("TIMES");
	//int_operators.push_back("DIVIDE");
	//int_operators.push_back("ATMOST");
	//int_operators.push_back("ATLEAST");
	//int_operators.push_back("LESS");
	//int_operators.push_back("MORE");
	//int_operators.push_back("EQUALS");

	for (int i = 0; i < int_operators.size(); i++) {
		integer_method_vector->push_back( 
				  new method_node(strdup(int_operators[i].c_str() ), 
					integer_f_args, 
					"Int", 
					new statement_block_node( new vector<statement_node*>()),	
					0) );
	}

	integer_method_vector->push_back( 
			new method_node("PRINT", 
				integer_f_args_print, 
				"Int", 
				new statement_block_node( new vector<statement_node*>()),	
				0) );

	class_node *Integer_class = new class_node(
			new class_sig_node("Int", new vector<f_arg_pair *>() , "Obj", 0), 
			new class_body_node(new vector <statement_node *>(), integer_method_vector), 
			0);

	class_vector->push_back(Integer_class);	

	// Class node for String 
	vector<method_node *> *string_method_vector = new vector<method_node *>();

	vector <f_arg_pair *> *string_f_args = new vector <f_arg_pair *>();
	string_f_args->push_back( new f_arg_pair("other", "String"));

	string_method_vector->push_back( new method_node("PLUS", 
				string_f_args, 
				"String", 
				new statement_block_node( new vector<statement_node*>()),	
				0) );

	string_method_vector->push_back( new method_node("EQUALS", 
				string_f_args, 
				"Boolean", 
				new statement_block_node( new vector<statement_node*>()),	
				0) );

	class_node *String_class = new class_node(
			new class_sig_node("String", new vector<f_arg_pair *>() , "Obj", 0), 
			new class_body_node(new vector <statement_node *>(), string_method_vector), 
			0);

	class_vector->push_back(String_class);

	// Class node for Boolean
	vector<method_node *> *boolean_method_vector = new vector<method_node *>();

	vector <f_arg_pair *> *boolean_f_args = new vector <f_arg_pair *>();
	boolean_f_args->push_back( new f_arg_pair("other", "Boolean"));

	vector <string> bool_operators;
	bool_operators.push_back("EQUALS");
	bool_operators.push_back("OR");
	bool_operators.push_back("AND");
	bool_operators.push_back("NOT");

	for (int i = 0; i < bool_operators.size(); i++) {
		boolean_method_vector->push_back( new method_node( 
					strdup(bool_operators[i].c_str() ),
					boolean_f_args, 
					"Boolean", 
					new statement_block_node( new vector<statement_node*>()),	
					0) );
	}

	class_node *Boolean_class = new class_node(
			new class_sig_node("Boolean", new vector<f_arg_pair *>() , "Obj", 0), 
			new class_body_node(new vector <statement_node *>(), boolean_method_vector), 
			0);

	class_vector->push_back(Boolean_class);

	// initalize the tree vector
	tree_vector = new vector <tree_node*>();

	vector<class_node *>::const_iterator c_iter;
	for (c_iter = class_vector->begin(); c_iter != class_vector->end(); ++c_iter) {
		(*c_iter)->build_classTree();
	}

	vector<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_vector->begin(); s_iter != statement_vector->end(); ++s_iter) {
		(*s_iter)->build_classTree();
	}

	return Obj_class->class_tree_node;
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
	vector<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_vector->begin(); s_iter != statement_vector->end(); ++s_iter) {
		(*s_iter)->build_classTree();
	}

	vector<method_node *>::const_iterator  m_iter;
	for (m_iter = method_vector->begin(); m_iter != method_vector->end(); ++m_iter) {
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
	// if class not in class vector print error
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

	vector<r_expr_node *>::const_iterator iter;
	for (iter = arg_vector->begin(); iter != arg_vector->end(); ++iter)
	{
		(*iter)->build_classTree();
	}

	return 0;
}

int method_call_node::build_classTree() 
{
	instance->build_classTree();

	vector<r_expr_node *>::const_iterator iter;
	for (iter = arg_vector->begin(); iter != arg_vector->end(); ++iter)
	{
		(*iter)->build_classTree();
	}
	return 0;	
}

int plus_node:: build_classTree()
{
	left->build_classTree();
	right->build_classTree();

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
