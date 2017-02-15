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

class_sig_node::class_sig_node(char *c_name, vector <f_arg_pair *> *f_args, const char *p) 
{
	class_name = c_name;
	formal_args = f_args;
	parent = p;
}

void class_sig_node::print() 
{

}

int class_sig_node::evaluate() 
{
	printf("Class signature node:\n");

	printf("class name: %s\n", class_name);

	printf("Formal Arguments:\n");
	for (int i = 0; i < formal_args->size(); i++) {
	  printf("formal_arg: %d\n", i);
		printf("  name: %s\n", (* formal_args)[i]-> name );
		printf("  type: %s\n", (* formal_args)[i]-> return_type ); 
	}

	printf("Parent: %s\n", parent);
}

class_node::class_node(class_sig_node *s, class_body_node *b) {
	sig = s;
	body = b;
}

void class_node::print() 
{

}

int class_node::evaluate() {

	printf("NODE: class\n");

	sig->evaluate();
	body->evaluate();
}

program_node::program_node(list <class_node *> *c, list <statement_node *> *s)
{
  class_list = c;
	statement_list = s;
}

void program_node::print() 
{

}

int program_node::evaluate() {

	printf("NODE: program\n");

	printf("  classes:\n");
	list<class_node *>::const_iterator c_iter;
	for (c_iter = class_list->begin(); c_iter != class_list->end(); ++c_iter) {
		(*c_iter)->evaluate();
	}
	
	printf("  statements:\n");
	list<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_list->begin(); s_iter != statement_list->end(); ++s_iter) {
		(*s_iter)->evaluate();
	}
}

method_node::method_node(char *name, vector < f_arg_pair * > *args, char *r_type, statement_block_node *b)
{
  method_name = name;
	formal_args = args;
	return_type = r_type;
	body = b;
}

void method_node::print() 
{

}

int method_node::evaluate() 
{
  printf("method_node:\n"); 

	printf("method name: %s\n", method_name);

	printf("formal_args: \n");

	for (int i = 0; i < formal_args->size(); i++) {
	  printf("formal_arg: %d\n", i);
		printf("  name: %s\n", (* formal_args)[i]-> name );
		printf("  type: %s\n", (* formal_args)[i]-> return_type ); 
	}

  if (return_type != NULL) {
		printf("return type: %s\n", return_type); 
	}

	printf("body:\n");

	body->evaluate();
}

class_body_node::class_body_node(list<statement_node *> *s_list, list<method_node *> *m_list)
{
	statement_list = s_list;
	method_list = m_list;
}

void class_body_node::print()
{
}

int class_body_node::evaluate()
{
	printf("class_body_node:\n");
  
	printf("statement_list:\n");
	list<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_list->begin(); s_iter != statement_list->end(); ++s_iter) {
		(*s_iter)->evaluate();
	}
  
	printf("method_list:\n");
	list<method_node *>::const_iterator  m_iter;
	for (m_iter = method_list->begin(); m_iter != method_list->end(); ++m_iter) {
		(*m_iter)->evaluate();
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


operator_node::operator_node(r_expr_node *L,const char* sym, r_expr_node *R) 
{
	left  = L;
	symbol = sym;
	right = R;
}

unary_node::unary_node(const char* sym, r_expr_node *R)
{
	symbol = sym;
	right = R;
}

void unary_node::print()
{
}

int unary_node::evaluate()
{
	printf("NODE: unary:\n");
	printf("operator: %s\n",symbol);
	right->evaluate();
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

times_node::times_node(r_expr_node *L, r_expr_node *R) : operator_node(L,R) {}

void times_node::print() {
	printf("(");
	left->print();
	printf(" * ");
	right->print();
	printf(")\n");
}

int times_node::evaluate() {
	int left_num, right_num;

	left_num = left->evaluate();
	right_num = right->evaluate();

	//num = left_num - right_num;

	printf("times_node: %d * %d \n", left_num, right_num);
	return num;
}

divide_node::divide_node(r_expr_node *L, r_expr_node *R) : operator_node(L,R) {}

void divide_node::print() {
	printf("(");
	left->print();
	printf(" / ");
	right->print();
	printf(")\n");
}

int divide_node::evaluate() {
	int left_num, right_num;

	left_num = left->evaluate();
	right_num = right->evaluate();

	num = left_num / right_num;

	printf("divide_node: %d / %d \n", left_num, right_num);
	return num;
}

compare_node::compare_node(r_expr_node *L, const char* sym, r_expr_node *R) : operator_node(L,sym,R){} 

void compare_node::print()
{
}

int compare_node::evaluate()
{
	printf("NODE: compare: \n");
	left->evaluate();
	printf("operation: %s\n", symbol);
	right->evaluate();
	printf("\n");
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

//Need to figure out how to use double inheritance for l-expr nad r-expr ident
int str_node::evaluate() {
	printf("str node: operand = %s\n", str);
	return 0;
}
