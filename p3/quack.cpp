#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include <cstdio>
#include "quack.h"
using namespace std;

elif_data::elif_data() {
 elif_conditions = new list < r_expr_node *>();
 elif_bodies = new list <statement_block_node*>();

 size = 0;

}

void elif_data::add(r_expr_node *new_cond, statement_block_node *new_body){
	elif_conditions->push_back(new_cond);
	elif_bodies->push_back(new_body);

	size++;
}

// if elseif
if_node::if_node(
		r_expr_node *if_c, 
		statement_block_node *if_b, 
		elif_data *elif_p) 
{
  // if
	if_condition = if_c;
	if_body = if_b;

  // else if
  elif_pairs = elif_p;
}

// if elseif else
if_node::if_node(
		r_expr_node *if_c,
		statement_block_node *if_b,
		elif_data *elif_p, 
		statement_block_node *else_b) 
{
  // if
	if_condition = if_c;
	if_body = if_b;

  // else if
  elif_pairs = elif_p;

  // else
  else_body = else_b;
}

void if_node::print() {	
	if_condition->print();
	if_body->print();
}

int if_node::evaluate() {
	//if
	printf("if node:\n");
	printf("if condition:\n");
	if_condition->evaluate();
	printf("if body\n");
	if_body->evaluate();

	//elseif
	list<r_expr_node *>::const_iterator c_iter;
	list<statement_block_node *>::const_iterator b_iter;

	c_iter = elif_pairs->elif_conditions->begin();
	b_iter = elif_pairs->elif_bodies->begin();

	for (int i = 0; i < elif_pairs->size; i++, c_iter++, b_iter++) {
		printf("Elif condition:\n");
		(*c_iter)->evaluate();

		printf("Elif body:\n");
		(*b_iter)->evaluate();
	}

	//else
	if(else_body != NULL)
	{	
		printf("else body:\n");
		else_body->evaluate();
	}

}

while_node::while_node(r_expr_node *cond, statement_block_node *stmts) {
	condition = cond;
	body = stmts;
}

void while_node::print() {
	condition->print();
	body->print();
}

int while_node::evaluate() {
	printf("while node:\n");
	printf("  condition:\n");
	condition->evaluate();
	printf("  body\n");
	body->evaluate();
}

statement_block_node::statement_block_node(list <statement_node *> *stmts) {
	statements = stmts;
}

int statement_block_node::evaluate() {
	list<statement_node *>::const_iterator iter;
	for (iter = statements->begin(); iter != statements->end(); ++iter) {
		//(*iter)->print();
		(*iter)->evaluate();
	}
}

void statement_block_node::print() {
	list<statement_node *>::const_iterator iter;
	for (iter = statements->begin(); iter != statements->end(); ++iter) {
		(*iter)->print();
	}
}

return_node::return_node(r_expr_node *rv) {
	return_value = rv;
}

void return_node::print() {
	if (return_value == NULL) 
		printf("empty\n");
	else 
		return_value->print();
}

int return_node::evaluate() {
	printf("return_node: return value =\n");
	if (return_value == NULL) 
		printf("empty\n");
	else 
		return_value->evaluate();
}

l_expr_node::l_expr_node(char *str)
{
	var = str;
}


l_expr_node::l_expr_node(r_expr_node *r_node, char *str)
{
	modifier = str;
	instance = r_node;
}

void l_expr_node::print(){
	
}

int l_expr_node::evaluate(){
	printf("l_expr_node:\n");
	if(var != NULL)
	{
		printf("  var: %s\n", var);
	}
	if(instance != NULL)
	{
		printf("  instance:\n");
		instance->evaluate();
	}
	if(modifier != NULL)
	{
		printf("  modifier: %s\n",modifier);
	}
	
	printf("\n");	
}

asgn_node::asgn_node(l_expr_node *left, r_expr_node *right)
{
	lhs = left;
	rhs = right;
}

asgn_node::asgn_node(l_expr_node *left,char *str, r_expr_node *right)
{
	lhs = left;
	rhs = right;
	c_name = str;
}

void asgn_node::print(){
}

int asgn_node::evaluate(){
	printf("asgn node:\n");
	printf("  lhs:\n");
	lhs->evaluate();
	
	if(c_name != NULL)
	{
		printf("  class: %s\n",c_name);
	}

	printf("  rhs:\n");
	rhs->evaluate();

	printf("\n");
}

constructor_call_node::constructor_call_node(char *str, list <r_expr_node *> *args) 
{
  c_name = str;
	arg_list = args;
}

void constructor_call_node::print() 
{

}

int constructor_call_node::evaluate() 
{
	printf("constructor_call_node:\n");

	printf("class: %s\n", c_name);

	// if class not in class list print error

	printf("arguments:\n");
	list<r_expr_node *>::const_iterator iter;
	for (iter = arg_list->begin(); iter != arg_list->end(); ++iter) {
		(*iter)->evaluate();
	}
}

method_call_node::method_call_node(r_expr_node *ins, char *mod, list <r_expr_node *> *args) 
{
  instance = ins;
	modifier = mod;
	arg_list = args;
}

void method_call_node::print() 
{

}

int method_call_node::evaluate() 
{
	printf("method_call_node:\n");

	printf("instance:\n");
	instance->evaluate();

	printf("modifier: %s\n", modifier);

	printf("arguments:\n");
	list<r_expr_node *>::const_iterator iter;
	for (iter = arg_list->begin(); iter != arg_list->end(); ++iter) {
		(*iter)->evaluate();
	}
	

}

operator_node::operator_node(r_expr_node *L, r_expr_node *R) 
{
	left  = L;
	right = R;
}


plus_node::plus_node(r_expr_node *L, r_expr_node *R) : operator_node(L,R) {}

void plus_node::print() {
	printf("(");
	left->print();
	printf(" + ");
	right->print();
	printf(")\n");
}

int plus_node::evaluate() {
	int left_num, right_num;

	left_num = left->evaluate();
	right_num = right->evaluate();

	num = left_num + right_num;

	printf("plus_node: %d + %d = %d\n", left_num, right_num, num);
	return num;
}

minus_node::minus_node(r_expr_node *L, r_expr_node *R) : operator_node(L,R) {}

void minus_node::print() {
	printf("(");
	left->print();
	printf(" - ");
	right->print();
	printf(")\n");
}

int minus_node::evaluate() {
	int left_num, right_num;

	left_num = left->evaluate();
	right_num = right->evaluate();

	num = left_num - right_num;

	printf("minus_node: %d - %d = %d\n", left_num, right_num, num);
	return num;
}


int_node::int_node(int value) {
	num = value;
}

void int_node::print() {
	printf("%d", num);
}

int int_node::evaluate() {
	printf("int node: operand = %d\n", num);
	return num;
}

str_node::str_node(char *value) {
	str = value;
}

void str_node::print() {
	printf("%s\n", str);
}

int str_node::evaluate() {
	printf("str node: operand = %s\n", str);
	return 0;
}
