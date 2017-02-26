#include <stdlib.h>
#include <string>
#include <string.h>
#include <map>
#include <list>
#include <cstdio>
#include "quack.h"
//#include "class_tree.h"
using namespace std;

// Type Checks
// - check for type errors
// - building var_table

// external data structures
extern vector < string > class_names;
extern list < tree_node *> *tree_list;
extern int error_flag;

map<string, string> var_table;

string if_node::type_checks() {
	if_condition->type_checks();
	if_body->type_checks();

	//elseif
	list<r_expr_node *>::const_iterator c_iter;
	list<statement_block_node *>::const_iterator b_iter;

	c_iter = elif_pairs->elif_conditions->begin();
	b_iter = elif_pairs->elif_bodies->begin();

	for (int i = 0; i < elif_pairs->size; i++, c_iter++, b_iter++) {
		(*c_iter)->type_checks();
		(*b_iter)->type_checks();
	}

	//else
	if(else_body != NULL)
	{	
		else_body->type_checks();
	}
	return "Nothing";
}

string while_node::type_checks() 
{
	string s1 = condition->type_checks();
	string lca = least_common_ancestor(s1,"Boolean");
	if (lca.compare("Boolean") != 0) {
		fprintf(stderr, "error:%d: while condition is of type \"%s\", type Boolean needed\n",lineno,lca.c_str()); 
		error();
	}

	body->type_checks();

	return "Nothing";
}

string statement_block_node::type_checks() 
{
	list<statement_node *>::const_iterator iter;
	for (iter = statements->begin(); iter != statements->end(); ++iter) {
		(*iter)->type_checks();
	}
	return "Nothing";
}

string class_sig_node::type_checks() 
{

	return "Nothing";
}

string class_node::type_checks() 
{
	sig->type_checks();
	body->type_checks();
	return "Nothing";
}

string program_node::type_checks() 
{

	var_table["true"] = "Boolean";
	var_table["false"] = "Boolean";

	list<class_node *>::const_iterator c_iter;
	for (c_iter = class_list->begin(); c_iter != class_list->end(); ++c_iter) {
		(*c_iter)->type_checks();
	}

	list<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_list->begin(); s_iter != statement_list->end(); ++s_iter) {
		(*s_iter)->type_checks();
	}
	return "Nothing";
}

string method_node::type_checks() 
{
	body->type_checks();
	return "Nothing";
}

string class_body_node::type_checks()
{
	list<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_list->begin(); s_iter != statement_list->end(); ++s_iter) {
		(*s_iter)->type_checks();
	}

	list<method_node *>::const_iterator  m_iter;
	for (m_iter = method_list->begin(); m_iter != method_list->end(); ++m_iter) {
		(*m_iter)->type_checks();
	}
	return "Nothing";
}

string return_node::type_checks() 
{
	if (return_value != NULL) 
		return_value->type_checks();
	return "Nothing";
}

string l_expr_node::type_checks()
{
	if(instance != NULL)
	{
		instance->type_checks();
	}

	// look up var in table of variables, return type of var
	string s(var);

	if (var_table.find(s) != var_table.end()) 
	{
		return var_table[s];
	}
	else 
	{
		fprintf(stderr, "error:%d : uninitalized variable %s\n", lineno, s.c_str() );
		error();
		return "Nothing";
	}

}

string assign_node::type_checks()
{
	string s1(lhs->var);
	string s2 = rhs->type_checks();

	// add var to table with least_common_ancestor of rhs, and vars old type
	if (var_table.find(s1) != var_table.end() ) {
		tree_node * lca = least_common_ancestor(get_tree_node(tree_list, var_table[s1]), 
				get_tree_node(tree_list, s2) );
		var_table[s1] = lca->name;
	}
	else {
		var_table[s1] = s2;
	}

	return "Nothing";
}

string constructor_call_node::type_checks() 
{

	list<r_expr_node *>::const_iterator iter;
	for (iter = arg_list->begin(); iter != arg_list->end(); ++iter) {
		(*iter)->type_checks();
	}

	string s(c_name);
	return s;
}

string method_call_node::type_checks() 
{
	instance->type_checks();


	list<r_expr_node *>::const_iterator iter;
	for (iter = arg_list->begin(); iter != arg_list->end(); ++iter) {
		(*iter)->type_checks();
	}

	// should be return type of method
	return "Nothing";
}

string unary_node::type_checks()
{
	string s = right->type_checks();

	if (!strcmp(symbol, "NOT") && s.compare("Boolean") ) {
			fprintf(stderr, "error:%d: \"not\" operation can only be applied to type \"Boolean\"\n", lineno);
			error();
			return "Nothing";
	}

	return s;
}

string plus_node::type_checks() 
{
	string s1 = left->type_checks();
	string s2 = right->type_checks();

	//check if divide exists in s1/s2 type

	if (s1.compare(s2) != 0) {
		fprintf(stderr,"error:%d: type mismatch %s is not of type %s\n",lineno,s1.c_str(), s2.c_str());
		error();
		return "Nothing";
	}
	else if (class_defines_method(get_tree_node(tree_list, s1), "PLUS") == 0){
		fprintf(stderr,"error:%d: PLUS not defined for class %s\n",lineno,s1.c_str());
		error();
		return "Nothing";
	}
	else {
		return s1;
	}
}

string minus_node::type_checks() 
{
	string s1 = left->type_checks();
	string s2 = right->type_checks();

	//check if divide exists in s1/s2 type

	if (s1.compare(s2) != 0) {
		fprintf(stderr,"error:%d: type mismatch %s is not of type %s\n",lineno,s1.c_str(), s2.c_str());
		error();
		return "Nothing";
	}
	else if (class_defines_method(get_tree_node(tree_list, s1), "MINUS") == 0){
		fprintf(stderr,"error:%d: MINUS not defined for class %s\n",lineno,s1.c_str());
		error();
		return "Nothing";
	}
	else {
		return s1;
	}
}

string times_node::type_checks() 
{
	string s1 = left->type_checks();
	string s2 = right->type_checks();

	//check if divide exists in s1/s2 type

	if (s1.compare(s2) != 0) {
		fprintf(stderr,"error:%d: type mismatch %s is not of type %s\n",lineno,s1.c_str(), s2.c_str());
    error();
		return "Nothing";
	}
	else if (class_defines_method(get_tree_node(tree_list, s1), "TIMES") == 0){
		fprintf(stderr,"error:%d: TIMES not defined for class %s\n",lineno,s1.c_str());
    error();
		return "Nothing";
	}
	else {
		return s1;
	}
}

string divide_node::type_checks() 
{
	string s1 = left->type_checks();
	string s2 = right->type_checks();

	//check if divide exists in s1/s2 type

	if (s1.compare(s2) != 0) {
		fprintf(stderr,"error:%d: type mismatch %s is not of type %s\n",lineno,s1.c_str(), s2.c_str());
    error();
		return "Nothing";
	}
	else if (class_defines_method(get_tree_node(tree_list, s1), "DIVIDE") == 0){
		fprintf(stderr,"error:%d: DIVIDE not defined for class %s\n",lineno,s1.c_str());
    error();
		return "Nothing";
	}
	else {
		return s1;
	}
}

string compare_node::type_checks()
{
	string s1 = left->type_checks();
	string s2 = right->type_checks();

	string symbol_string(symbol);

	if (s1.compare(s2) != 0) {
		fprintf(stderr,"error:%d: type mismatch. %s does not match %s\n", lineno, s1.c_str(), s2.c_str() );
    error();
		return "Nothing";
	}
	else if (class_defines_method(get_tree_node(tree_list, s1), symbol_string) == 0){
		fprintf(stderr,"error:%d: %s not defined for class %s\n", lineno, symbol, s1.c_str() );
    error();
		return "Nothing";
	}
	else {
		return "Boolean";
	}
}

string int_node::type_checks() 
{
	return "Int";
}

string str_node::type_checks() 
{
	return "String";
}
