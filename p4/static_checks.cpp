#include <stdlib.h>
#include <string>
#include <string.h>
#include <map>
#include <list>
#include <cstdio>
#include "quack.h"
//#include "class_tree.h"
using namespace std;


// Static Checks
// - constructor call exists for class

// external data structures
extern vector < string > class_names;
extern list < tree_node *> *tree_list;

int if_node::static_checks() {
	if_condition->static_checks();
	if_body->static_checks();

	//elseif
	list<r_expr_node *>::const_iterator c_iter;
	list<statement_block_node *>::const_iterator b_iter;

	c_iter = elif_pairs->elif_conditions->begin();
	b_iter = elif_pairs->elif_bodies->begin();

	for (int i = 0; i < elif_pairs->size; i++, c_iter++, b_iter++) {
		(*c_iter)->static_checks();
		(*b_iter)->static_checks();
	}

	//else
	if(else_body != NULL)
	{	
		else_body->static_checks();
	}
}

int while_node::static_checks() 
{
	condition->static_checks();
	body->static_checks();
}

int statement_block_node::static_checks() 
{
	list<statement_node *>::const_iterator iter;
	for (iter = statements->begin(); iter != statements->end(); ++iter) {
		(*iter)->static_checks();
	}
}

int class_sig_node::static_checks() 
{

}


int class_node::static_checks() 
{
	sig->static_checks();
	body->static_checks();
}

int program_node::static_checks() 
{
	list<class_node *>::const_iterator c_iter;
	for (c_iter = class_list->begin(); c_iter != class_list->end(); ++c_iter) {
		(*c_iter)->static_checks();
	}

	list<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_list->begin(); s_iter != statement_list->end(); ++s_iter) {
		(*s_iter)->static_checks();
	}
}

int method_node::static_checks() 
{
	body->static_checks();
}

int class_body_node::static_checks()
{
	list<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_list->begin(); s_iter != statement_list->end(); ++s_iter) {
		(*s_iter)->static_checks();
	}

	list<method_node *>::const_iterator  m_iter;
	for (m_iter = method_list->begin(); m_iter != method_list->end(); ++m_iter) {
		(*m_iter)->static_checks();
	}
}

int return_node::static_checks() 
{
	if (return_value != NULL) 
		return_value->static_checks();
}

int l_expr_node::static_checks()
{
	if(instance != NULL)
	{
		instance->static_checks();
	}
}

int assign_node::static_checks(){
	lhs->static_checks();
	rhs->static_checks();
}

int constructor_call_node::static_checks() 
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
		(*iter)->static_checks();
	}
}

int method_call_node::static_checks() 
{
	instance->static_checks();

        // 


	list<r_expr_node *>::const_iterator iter;
	for (iter = arg_list->begin(); iter != arg_list->end(); ++iter) {
		(*iter)->static_checks();
	}
}

int unary_node::static_checks()
{
	right->static_checks();
}

int plus_node::static_checks() 
{
	left->static_checks();
	right->static_checks();
}

int minus_node::static_checks() 
{
	left->static_checks();
	right->static_checks();
}

int times_node::static_checks() 
{
	left->static_checks();
	right->static_checks();
}

int divide_node::static_checks() 
{
	left->static_checks();
	right->static_checks();
}

int compare_node::static_checks()
{
	left->static_checks();
	right->static_checks();
}

int int_node::static_checks() 
{

}

int str_node::static_checks() 
{

}
