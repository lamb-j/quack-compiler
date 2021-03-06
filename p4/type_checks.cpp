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
extern int sweep;

string current_method;
string current_class;


string if_node::type_checks( map< string, string > *local, map< string, string > *field ) {

	string c, lca; // condition, least common ancestor
	
	c = if_condition->type_checks(local, field);
	lca = least_common_ancestor(c, "Boolean");

	if (lca.compare("Boolean") != 0) {
		fprintf(stderr, "error:%d: if condition is of type \"%s\", type Boolean needed\n", lineno, c.c_str()); 
		error();
	}

	if_body->type_checks(local, field);

	//elseif
	list<r_expr_node *>::const_iterator c_iter;
	list<statement_block_node *>::const_iterator b_iter;

	c_iter = elif_pairs->elif_conditions->begin();
	b_iter = elif_pairs->elif_bodies->begin();

	for (int i = 0; i < elif_pairs->size; i++, c_iter++, b_iter++) {
		c = (*c_iter)->type_checks(local, field);
		lca = least_common_ancestor(c,"Boolean");
		if (lca.compare("Boolean") != 0) {
			fprintf(stderr, "error:%d: elif condition is of type \"%s\", type Boolean needed\n", lineno, c.c_str()); 
			error();
		}
		(*b_iter)->type_checks(local, field);
	}

	//else
	if(else_body != NULL)
	{	
		else_body->type_checks(local, field);
	}
	return "Nothing";
}

string while_node::type_checks( map< string, string > *local, map< string, string > *field ) 
{
	string s1 = condition->type_checks(local, field);
	string lca = least_common_ancestor(s1,"Boolean");
	if (lca.compare("Boolean") != 0) {
		fprintf(stderr, "error:%d: while condition is of type \"%s\", type Boolean needed\n", lineno, s1.c_str()); 
		error();
	}

	body->type_checks(local, field);

	return "Nothing";
}

string statement_block_node::type_checks( map< string, string > *local, map< string, string > *field ) 
{
	list<statement_node *>::const_iterator iter;
	for (iter = statements->begin(); iter != statements->end(); ++iter) {
		(*iter)->type_checks(local, field);
	}
	return "Nothing";
}

string class_sig_node::type_checks( map< string, string > *local, map< string, string > *field ) 
{

	current_class = string(class_name);

	// iterate over args and add to local table
  for (int i = 0; i < formal_args->size(); i++ ) {
		if (local->find( ( *formal_args)[i]->name ) == local->end() ) 
			(*local)[(*formal_args)[i]->name] = (*formal_args)[i]->return_type;
	}

	return "Nothing";
}
//local and field map are NULL. Maps are generated here
string class_node::type_checks( map< string, string > *local, map< string, string > *field ) 
{

	if( local_var_table == NULL )
		local_var_table = new map< string, string>();
	if (field_var_table == NULL )
		field_var_table = new map< string, string>();

	if (class_tree_node->parent->name.compare("")) //if parent is not "" i.e class is not Obj
	{
		add_parent_methods( class_tree_node->parent->AST_node->body->method_list, 
												body->method_list, 
												string(sig->class_name) );
		

		if (sweep == 2) {
			map<string,string> *tmp = class_tree_node->parent->AST_node->field_var_table;

			if (tmp == NULL) printf("NULL ERROR\n");

			if( tmp != NULL)
			{
				add_parent_fields( tmp, field_var_table);
			}

		}
	}


	(*local_var_table)["true"] = "Boolean";
  (*local_var_table)["false"] = "Boolean";

	sig->type_checks(local_var_table,field_var_table);
	body->type_checks(local_var_table, field_var_table);
	return "Nothing";
}

string program_node::type_checks(tree_node *root) 
{

	if( stmt_var_table == NULL)
		stmt_var_table = new map< string, string>();

	(*stmt_var_table)["true"] = "Boolean";
  (*stmt_var_table)["false"] = "Boolean";

	//list<class_node *>::const_iterator c_iter;
	//for (c_iter = class_list->begin(); c_iter != class_list->end(); ++c_iter) {
  //	(*c_iter)->type_checks(NULL, NULL);
	//}

	// type_check in order from root to children
	type_check_class(root);

	list<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_list->begin(); s_iter != statement_list->end(); ++s_iter) {
		(*s_iter)->type_checks(stmt_var_table, NULL);
	}

	return "Nothing";
}

string method_node::type_checks( map< string, string > *local, map< string, string > *field ) 
{
	
	meth_var_table = new map <string, string>();

	current_method = string(method_name);

  for (int i = 0; i < formal_args->size(); i++ ) {
		if (meth_var_table->find( ( *formal_args)[i]->name ) == meth_var_table->end() ) 
			(*meth_var_table)[(*formal_args)[i]->name] = (*formal_args)[i]->return_type;
	}
	body->type_checks(meth_var_table, field);
	return "Nothing";
}

string class_body_node::type_checks( map< string, string > *local, map< string, string > *field )
{
	list<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_list->begin(); s_iter != statement_list->end(); ++s_iter) {
		(*s_iter)->type_checks(local, field);
	}

	list<method_node *>::const_iterator  m_iter;
	for (m_iter = method_list->begin(); m_iter != method_list->end(); ++m_iter) {
		(*m_iter)->type_checks(local, field);
	}
	return "Nothing";
}

string return_node::type_checks( map< string, string > *local, map< string, string > *field ) 
{
	string s;
	method_node * calling_method = get_AST_method_node(current_class, current_method);

	if (return_value != NULL && calling_method->return_type != NULL) {
		s = return_value->type_checks(local, field);

		string lca = least_common_ancestor(s, string(calling_method->return_type));
		if (string(calling_method->return_type).compare( lca ) != 0) {
			fprintf(stderr, "error:%d: Return type of %s does not match declared return type of %s\n",
					lineno, s.c_str(), calling_method->return_type);
			error();
			return "Nothing";
		}

	}
	else if (return_value != NULL && calling_method->return_type == NULL) {
		s = return_value->type_checks(local, field);

		fprintf(stderr, "error:%d: Method does not define return type, return type of %s present\n", lineno, s.c_str());
		error();
  }
	else if (return_value == NULL && calling_method->return_type == NULL) {
		return "Nothing";
	}

	else {
		fprintf(stderr, "error:%d: return statement must be of type %s\n", lineno, calling_method->return_type);
		error();
	}

	return "Nothing";
}

// This rule only reachable from R_expr -> L_expr -> IDENT
//   fix by making ident_node extends R_expr_node, and fixing ambiguity in parser
string l_expr_node::type_checks( map< string, string > *local, map< string, string > *field )
{

	// var case
	if (var != NULL) {
		// look up var in table of variables, return type of var
		string s(var);

		if (local->find(s) != local->end()) 
		{
			return (*local)[s];
		}
		else 
		{
			fprintf(stderr, "error:%d : uninitalized variable %s\n", lineno, s.c_str() );
			error();
			return "Nothing";
		}
	}

	if (field == NULL ) {
		fprintf(stderr, "error:%d: cannot access field values outside class\n", lineno);
		error();
		return "Nothing";
	}

	// instance / modifier case
	if (modifier != NULL) {
		// look up modifier in table of modifieriables, return type of modifier
		string s(modifier);

		if (field->find(s) != field->end()) 
		{
			return (*field)[s];
		}
		else 
		{
			fprintf(stderr, "error:%d : uninitalized field %s\n", lineno, s.c_str() );
			error();
			return "Nothing";
		}
	}

}

string assign_node::type_checks( map< string, string > *local, map< string, string > *field )
{

	// var case
	if (lhs->var != NULL) {
		string s1 = string(lhs->var);
		string s2 = rhs->type_checks(local, field);

		// add var to table with least_common_ancestor of rhs, and vars old type
		if (local->find(s1) != local->end() ) {
			string lca = least_common_ancestor((*local)[s1], s2 );
			(*local)[s1] = lca;
		}
		else {
			(*local)[s1] = s2;
		}

	}

	// field case
  else {

		// deal with instance somehow

		// add modifier to field table with least_common_ancestor of rhs, and modifier old type
		string s1 = string(lhs->modifier);
		string s2 = rhs->type_checks(local, field);


		if (field == NULL ) {
			fprintf(stderr, "error:%d: cannot access field values outside class\n", lineno);
			error();
			return "Nothing";
		}

		//if field exists - update type as lca
		if (field->find(s1) != field->end() ) {
			string lca = least_common_ancestor( (*field)[s1] , s2 );
			(*field)[s1] = lca;
		}
		else {
			(*field)[s1] = s2;
		}

	}


	return "Nothing";
}

string constructor_call_node::type_checks( map< string, string > *local, map< string, string > *field ) 
{

	list<r_expr_node *>::const_iterator iter;
	for (iter = arg_list->begin(); iter != arg_list->end(); ++iter) {
		(*iter)->type_checks(local, field);
	}

	string s(c_name);
	return s;
}

// may need to push this out to static_checks.cpp to avoid wrong error messages
string method_call_node::type_checks( map< string, string > *local, map< string, string > *field ) 
{

	if (sweep == 2) {

		string s1 = instance->type_checks(local, field);

		method_node *AST_method_node = get_AST_method_node (s1, string(modifier) ); 

		if (AST_method_node == NULL) {
			fprintf(stderr, "error:%d: Method %s not found in class %s\n", lineno, modifier, s1.c_str());
			error();
			return "Nothing";
		}


		// check arg_list (list r_expr_node*)  against AST_method_node->formal_args (vector f_arg_pair*)
		list<r_expr_node *>::const_iterator iter;

		//check1: length of arg list  vs length of foraml args
		if( arg_list->size() != AST_method_node->formal_args->size() )
		{
			fprintf(stderr,"error:%d Incorrect number of arguments. Method defined at lineno:%d\n",lineno, AST_method_node->lineno);	
			error();
			return "Nothing";
		}
		int i;	
		for (iter = arg_list->begin(),i=0; iter != arg_list->end(); ++iter, ++i) {
			string arg_type = (*iter)->type_checks(local, field);
			string formal_arg_type = (*AST_method_node->formal_args)[i]->return_type;

			if( !is_subclass(arg_type, formal_arg_type) )
			{
				fprintf(stderr,"error:%d: argument %d of type %s does not match formal argument of type %s in method %s\n",
						lineno,  (int) (arg_list->size() - i - 1), arg_type.c_str(), formal_arg_type.c_str(), AST_method_node->method_name);
				error();
			}

		}

		// should be return type of method
		return string(AST_method_node->return_type);
	}

	return "Dummy";
}

string unary_node::type_checks( map< string, string > *local, map< string, string > *field )
{
	string s = right->type_checks(local, field);

	if (!strcmp(symbol, "NOT") && s.compare("Boolean") ) {
		fprintf(stderr, "error:%d: \"not\" operation can only be applied to type \"Boolean\"\n", lineno);
		error();
		return "Nothing";
	}

	return s;
}

string plus_node::type_checks( map< string, string > *local, map< string, string > *field ) 
{
	string s1 = left->type_checks(local, field);
	string s2 = right->type_checks(local, field);

	if (sweep == 2) {
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
	}
	return s1;
}

string minus_node::type_checks( map< string, string > *local, map< string, string > *field ) 
{
	string s1 = left->type_checks(local, field);
	string s2 = right->type_checks(local, field);

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

string times_node::type_checks( map< string, string > *local, map< string, string > *field ) 
{
	string s1 = left->type_checks(local, field);
	string s2 = right->type_checks(local, field);

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

string divide_node::type_checks( map< string, string > *local, map< string, string > *field ) 
{
	string s1 = left->type_checks(local, field);
	string s2 = right->type_checks(local, field);

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

string compare_node::type_checks( map< string, string > *local, map< string, string > *field )
{
	string s1 = left->type_checks(local, field);
	string s2 = right->type_checks(local, field);

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

string int_node::type_checks( map< string, string > *local, map< string, string > *field ) 
{
	return "Int";
}

string str_node::type_checks( map< string, string > *local, map< string, string > *field ) 
{
	return "String";
}
