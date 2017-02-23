#include <stdlib.h>
#include <string>
#include <string.h>
#include <map>
#include <list>
#include <cstdio>
#include "quack.h"
#include "class_tree.h"
using namespace std;

extern vector < string > class_names;

void if_node::print(int indent) {
	//if
	printf("%*sNODE: if\n", indent, "");
	printf("%*sif condition:\n", indent + 2, "");
	if_condition->print(indent + 4);
	printf("%*sif body\n", indent + 2, "");
	if_body->print(indent + 4);

	//elseif
	list<r_expr_node *>::const_iterator c_iter;
	list<statement_block_node *>::const_iterator b_iter;

	c_iter = elif_pairs->elif_conditions->begin();
	b_iter = elif_pairs->elif_bodies->begin();

	for (int i = 0; i < elif_pairs->size; i++, c_iter++, b_iter++) {
		printf("%*selif condition:\n", indent + 2, "");
		(*c_iter)->print(indent + 4);

		printf("%*selif body:\n", indent + 2, "");
		(*b_iter)->print(indent + 4);
	}

	//else
	if(else_body != NULL)
	{	
		printf("%*selse body:\n", indent + 2, "");
		else_body->print(indent + 4);
	}

}

void while_node::print(int indent) {
	printf("%*sNODE: while\n", indent, "");
	printf("%*scondition:\n", indent + 2, "");
	condition->print(indent + 4);
	printf("%*sbody\n", indent + 2, "");
	body->print(indent + 4);
}

void statement_block_node::print(int indent) {
	list<statement_node *>::const_iterator iter;
	for (iter = statements->begin(); iter != statements->end(); ++iter) {
		(*iter)->print(indent + 4);
	}
}

void class_sig_node::print(int indent) 
{
	printf("%*sNODE: class signature\n", indent, "");

	printf("%*sclass name: %s\n", indent + 2, "", class_name);

	printf("%*sformal arguments:\n", indent + 2, "");
	for (int i = 0; i < formal_args->size(); i++) {
		printf("%*sarg:%d name: %s type:%s\n", indent + 3, "", i, (* formal_args)[i]-> name , (* formal_args)[i]->return_type );
	}

	printf("%*sparent: %s\n", indent + 2, "", parent);
  	
	//int flag = 1;
	//for(int i=0; i<class_names.size(); i++)
//	{
//		if(strcmp(parent, class_names[i].c_str() ) == 0 ) flag = 0;
//	}
//
//	if (flag)	fprintf(stderr,"****parent class %s not defined****\n",parent);

}

void class_node::print(int indent) {

	printf("%*sNODE: class\n", indent, "");

	sig->print(indent + 4);
	body->print(indent + 4);
}

void program_node::print(int indent) {

	printf("%*sNODE: program\n", indent, "");

	printf("%*sclasses:\n", indent + 2, "");
	list<class_node *>::const_iterator c_iter;
	for (c_iter = class_list->begin(); c_iter != class_list->end(); ++c_iter) {
		(*c_iter)->print(indent + 4);
	}

	printf("%*sstatements:\n", indent + 2, "");
	list<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_list->begin(); s_iter != statement_list->end(); ++s_iter) {
		(*s_iter)->print(indent + 4);
	}
}

void method_node::print(int indent) 
{
	printf("%*sNODE: method\n", indent, ""); 

	printf("%*smethod name: %s\n", indent + 2, "", method_name);

	printf("%*sformal_args:\n", indent + 2, "");

	for (int i = 0; i < formal_args->size(); i++) {
		printf("%*sarg:%d name: %s type:%s\n", indent + 3, "", i, (* formal_args)[i]-> name , (* formal_args)[i]->return_type );
	}

	if (return_type != NULL) {
		printf("%*sreturn type: %s\n", indent + 2, "", return_type); 
	}

	printf("%*sbody:\n", indent + 2, "");
	body->print(indent + 4);
}

void class_body_node::print(int indent)
{
	printf("%*sNODE: class body\n", indent, "");

	printf("%*sstatement_list:\n", indent + 2, "");
	list<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_list->begin(); s_iter != statement_list->end(); ++s_iter) {
		(*s_iter)->print(indent + 4);
	}

	printf("%*smethod_list:\n", indent + 2, "");
	list<method_node *>::const_iterator  m_iter;
	for (m_iter = method_list->begin(); m_iter != method_list->end(); ++m_iter) {
		(*m_iter)->print(indent + 4);
	}
}

void return_node::print(int indent) {
	printf("%*sNODE: return\n", indent, "");
	printf("%*svalue:\n", indent + 2, "");
	if (return_value == NULL) 
		printf("%*sempty\n", indent + 4, "");
	else 
		return_value->print(indent + 4);
}

void l_expr_node::print(int indent){
	printf("%*sNODE: l_expr\n", indent, "");
	if(var != NULL)
	{
		printf("%*svar: %s\n", indent + 2, "", var);
	}
	if(instance != NULL)
	{
		printf("%*sinstance:\n", indent + 2, "");
		instance->print(indent + 4);
	}
	if(modifier != NULL)
	{
		printf("%*smodifier: %s\n", indent + 2, "", modifier);
	}

}

void asgn_node::print(int indent){
	printf("%*sNODE: asgn\n", indent, "");
	printf("%*slhs:\n", indent + 2, "");
	lhs->print(indent + 4);

	if(c_name != NULL)
	{
		printf("%*sclass: %s\n", indent + 2, "", c_name);
	}

	printf("%*srhs:\n", indent + 2, "");
	rhs->print(indent + 4);

}

void constructor_call_node::print(int indent) 
{
	printf("%*sNODE: constructor call\n", indent, "");

	printf("%*sclass: %s\n", indent + 2, "", c_name);

	// if class not in class list print error

	//int flag = 1;
	//for(int i=0; i<class_names.size(); i++)
	//{
	//	if(strcmp(c_name, class_names[i].c_str() ) == 0 ) flag = 0;
	//}

	//if (flag)	fprintf(stderr,"****class %s not defined****\n",c_name);

	printf("%*sarguments:\n", indent + 2, "");
	list<r_expr_node *>::const_iterator iter;
	for (iter = arg_list->begin(); iter != arg_list->end(); ++iter) {
		(*iter)->print(indent + 4);
	}
}

void method_call_node::print(int indent) 
{
	printf("%*sNODE: method call\n", indent, "");

	printf("%*sinstance:\n", indent + 2, "");
	instance->print(indent + 4);

	printf("%*smodifier: %s\n", indent + 2, "", modifier);

	printf("%*sarguments:\n", indent + 2, "");
	list<r_expr_node *>::const_iterator iter;
	for (iter = arg_list->begin(); iter != arg_list->end(); ++iter) {
		(*iter)->print(indent + 4);
	}
}

void unary_node::print(int indent)
{
	printf("%*sNODE: unary:\n", indent, "");
	printf("%*soperator: %s\n", indent + 2, "", symbol);
	printf("%*sright:\n", indent + 2, "");
	right->print(indent + 4);
}

void plus_node::print(int indent) {
	printf("%*sNODE: minus\n", indent, "");
	printf("%*sleft:\n", indent + 2, "");
  left->print(indent + 4);
	printf("%*sright:\n", indent + 2, "");
	right->print(indent + 4);
}

void minus_node::print(int indent) {
	printf("%*sNODE: minus\n", indent, "");
	printf("%*sleft:\n", indent + 2, "");
  left->print(indent + 4);
	printf("%*sright:\n", indent + 2, "");
	right->print(indent + 4);
}

void times_node::print(int indent) {
	printf("%*sNODE: times\n", indent, "");
	printf("%*sleft:\n", indent + 2, "");
  left->print(indent + 4);
	printf("%*sright:\n", indent + 2, "");
	right->print(indent + 4);
}

void divide_node::print(int indent) {

	printf("%*sNODE: divide\n", indent, "");
	printf("%*sleft:\n", indent + 2, "");
  left->print(indent + 4);
	printf("%*sright:\n", indent + 2, "");
	right->print(indent + 4);
}

void compare_node::print(int indent)
{
	printf("%*sNODE: compare\n", indent, "");
	printf("%*sleft:\n", indent + 2, "");
	left->print(indent + 4);
	printf("%*soperation: %s\n", indent + 2, "", symbol);
	printf("%*sright:\n", indent + 2, "");
	right->print(indent + 4);
}

void int_node::print(int indent) {
	printf("%*sNODE: int\n", indent, "");
	printf("%*svalue: %d\n", indent + 2, "", num);
}

//Need to figure out how to use double inheritance for l-expr nad r-expr indent
void str_node::print(int indent) {
	printf("%*sNODE: str\n", indent, "");
	printf("%*sstring: %s\n", indent + 2, "", str);
}
