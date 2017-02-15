#include <stdlib.h>
#include <string>
#include <string.h>
#include <map>
#include <list>
#include <cstdio>
#include "quack.h"
using namespace std;

vector < string > class_names;

// Data structure for handling elif conditions
elif_data::elif_data() 
{
	elif_conditions = new list < r_expr_node *>();
	elif_bodies = new list <statement_block_node*>();

	size = 0;
}

void elif_data::add(r_expr_node *new_cond, statement_block_node *new_body)
{
	elif_conditions->push_back(new_cond);
	elif_bodies->push_back(new_body);

	size++;
}

// -----
// Node constructors 

// if elseif constructor
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

while_node::while_node(r_expr_node *cond, statement_block_node *stmts) 
{
	condition = cond;
	body = stmts;
}

statement_block_node::statement_block_node(list <statement_node *> *stmts) 
{
	statements = stmts;
}

class_sig_node::class_sig_node(char *c_name, vector <f_arg_pair *> *f_args, const char *p) 
{
	class_name = c_name;
	formal_args = f_args;
	parent = p;
}

class_node::class_node(class_sig_node *s, class_body_node *b) 
{
	sig = s;
	body = b;
}

program_node::program_node(list <class_node *> *c, list <statement_node *> *s)
{
	class_list = c;
	statement_list = s;
}

method_node::method_node(char *name, vector < f_arg_pair * > *args, char *r_type, statement_block_node *b)
{
	method_name = name;
	formal_args = args;
	return_type = r_type;
	body = b;
}

class_body_node::class_body_node(list<statement_node *> *s_list, list<method_node *> *m_list)
{
	statement_list = s_list;
	method_list = m_list;
}

return_node::return_node(r_expr_node *rv) {
	return_value = rv;
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

constructor_call_node::constructor_call_node(char *str, list <r_expr_node *> *args) 
{
	c_name = str;
	arg_list = args;
}

method_call_node::method_call_node(r_expr_node *ins, char *mod, list <r_expr_node *> *args) 
{
	instance = ins;
	modifier = mod;
	arg_list = args;
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

plus_node::plus_node(r_expr_node *L, r_expr_node *R) : operator_node(L,R) {}

minus_node::minus_node(r_expr_node *L, r_expr_node *R) : operator_node(L,R) {}

times_node::times_node(r_expr_node *L, r_expr_node *R) : operator_node(L,R) {}

divide_node::divide_node(r_expr_node *L, r_expr_node *R) : operator_node(L,R) {}

compare_node::compare_node(r_expr_node *L, const char* sym, r_expr_node *R) : operator_node(L,sym,R){} 

int_node::int_node(int value) {
	num = value;
}

str_node::str_node(char *value) {
	str = value;
}
