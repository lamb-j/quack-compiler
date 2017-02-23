#include <stdlib.h>
#include <string>
#include <string.h>
#include <map>
#include <list>
#include <cstdio>
#include "quack.h"
#include "class_tree.h"
using namespace std;

// external data structures
extern vector < string > class_names;
extern list < tree_node *> *tree_list;

int if_node::evaluate() {
	if_condition->evaluate();
	if_body->evaluate();

	//elseif
	list<r_expr_node *>::const_iterator c_iter;
	list<statement_block_node *>::const_iterator b_iter;

	c_iter = elif_pairs->elif_conditions->begin();
	b_iter = elif_pairs->elif_bodies->begin();

	for (int i = 0; i < elif_pairs->size; i++, c_iter++, b_iter++) {
		(*c_iter)->evaluate();
		(*b_iter)->evaluate();
	}

	//else
	if(else_body != NULL)
	{	
		else_body->evaluate();
	}
}

int while_node::evaluate() 
{
	condition->evaluate();
	body->evaluate();
}

int statement_block_node::evaluate() 
{
	list<statement_node *>::const_iterator iter;
	for (iter = statements->begin(); iter != statements->end(); ++iter) {
		(*iter)->evaluate();
	}
}

int class_sig_node::evaluate() 
{
	// check if parent class is defined (in the list)
	int flag = 1;
	for(int i=0; i<class_names.size(); i++)
	{
		if(strcmp(parent, class_names[i].c_str() ) == 0 ) flag = 0;
	}

	if (flag)	fprintf(stderr,"error: parent class %s not defined\n",parent);

	//check if class name among default classes
	const char* default_classes[] = { "Obj", "Int", "Nothing", "String", "Boolean" };
	
	for( int i=0; i<5; i++)
	{
		if(! strcmp( class_name, default_classes[i]))
			fprintf(stderr,"error: class name %s is a default class\n",class_name); 
	}

	//check if class extends itself
	if( strcmp( parent, class_name) == 0)
		fprintf(stderr,"error: class %s cannot extend %s\n",class_name,parent);


        // add class to tree_list
        string p(parent);
        string c(class_name);
        append_tree(tree_list, p, c);
}


int class_node::evaluate() 
{
	sig->evaluate();
	body->evaluate();
}

int program_node::evaluate() 
{
	list<class_node *>::const_iterator c_iter;
	for (c_iter = class_list->begin(); c_iter != class_list->end(); ++c_iter) {
		(*c_iter)->evaluate();
	}

	list<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_list->begin(); s_iter != statement_list->end(); ++s_iter) {
		(*s_iter)->evaluate();
	}
}

int method_node::evaluate() 
{
	body->evaluate();
}

int class_body_node::evaluate()
{
	list<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_list->begin(); s_iter != statement_list->end(); ++s_iter) {
		(*s_iter)->evaluate();
	}

	list<method_node *>::const_iterator  m_iter;
	for (m_iter = method_list->begin(); m_iter != method_list->end(); ++m_iter) {
		(*m_iter)->evaluate();
	}
}

int return_node::evaluate() 
{
	if (return_value != NULL) 
		return_value->evaluate();
}

int l_expr_node::evaluate()
{
	if(instance != NULL)
	{
		instance->evaluate();
	}
}

int asgn_node::evaluate(){
	lhs->evaluate();
	rhs->evaluate();
}

int constructor_call_node::evaluate() 
{
	// if class not in class list print error
	int flag = 1;
	for(int i=0; i<class_names.size(); i++)
	{
		if(strcmp(c_name, class_names[i].c_str() ) == 0 ) flag = 0;
	}

	if (flag)	fprintf(stderr,"error: class %s not defined\n",c_name);

	list<r_expr_node *>::const_iterator iter;
	for (iter = arg_list->begin(); iter != arg_list->end(); ++iter) {
		(*iter)->evaluate();
	}
}

int method_call_node::evaluate() 
{
	instance->evaluate();

	list<r_expr_node *>::const_iterator iter;
	for (iter = arg_list->begin(); iter != arg_list->end(); ++iter) {
		(*iter)->evaluate();
	}
}

int unary_node::evaluate()
{
	right->evaluate();
}

int plus_node::evaluate() 
{
	left->evaluate();
	right->evaluate();
}

int minus_node::evaluate() 
{
	left->evaluate();
	right->evaluate();
}

int times_node::evaluate() 
{
	left->evaluate();
	right->evaluate();
}

int divide_node::evaluate() 
{
	left->evaluate();
	right->evaluate();
}

int compare_node::evaluate()
{
	left->evaluate();
	right->evaluate();
}

int int_node::evaluate() 
{

}

//Need to figure out how to use double inheritance for l-expr nad r-expr ident
int str_node::evaluate() 
{

}
