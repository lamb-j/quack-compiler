#include <stdlib.h>
#include <string>
#include <string.h>
#include <map>
#include <vector>
#include <cstdio>
#include "quack.h"
//#include "class_tree.h"
using namespace std;

// Type Checks
// - check for type errors
// - building var_table

// external data structures
extern vector < string > class_names;
extern vector < tree_node *> *tree_vector;
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
	vector<r_expr_node *>::const_iterator c_iter;
	vector<statement_block_node *>::const_iterator b_iter;

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
	for (int i=0; i< statements->size(); i++)
	{
		(*statements)[i]->type_checks(local,field);
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
		if (sweep == 2) {
      add_parent_methods( class_tree_node->parent->AST_node->body->method_vector, 
												body->method_vector, 
											  string(sig->class_name) );
		

		//if (sweep == 2) {
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

	if ( sweep == 1 ) {
		stmt_var_table = new map< string, string>();
  }

	(*stmt_var_table)["true"] = "Boolean";
  (*stmt_var_table)["false"] = "Boolean";

	// type_check in order from root to children
	type_check_class(root);

	current_method = "MAIN";

	for(int i = 0; i < statement_vector->size(); i++)
	{
		(*statement_vector)[i]->type_checks(stmt_var_table, NULL);
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
	vector<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_vector->begin(); s_iter != statement_vector->end(); ++s_iter) {
		(*s_iter)->type_checks(local, field);
	}

	vector<method_node *>::const_iterator  m_iter;
	for (m_iter = method_vector->begin(); m_iter != method_vector->end(); ++m_iter) {
		(*m_iter)->type_checks(local, field);
	}
	return "Nothing";
}

string return_node::type_checks( map< string, string > *local, map< string, string > *field ) 
{
	string s;

	if (!current_method.compare("MAIN")) {
		fprintf( stderr, "error:%d: Return statement not allowed outside of method definitions\n", lineno);
		error();
		return "Nothing";
	}

	method_node * calling_method = get_AST_method_node(current_class, current_method);

	if (return_value != NULL && calling_method->return_type != NULL) {
		s = return_value->type_checks(local, field);

		string lca = least_common_ancestor(s, string(calling_method->return_type));
		if (string(calling_method->return_type).compare( lca ) != 0) {
			fprintf(stderr, "error:%d: Return type of '%s' does not match declared return type of '%s' for method '%s'\n",
					lineno, s.c_str(), calling_method->return_type, current_method.c_str() );
			error();
			return "Nothing";
		}

	}
	else if (return_value != NULL && calling_method->return_type == NULL) {
		s = return_value->type_checks(local, field);

		fprintf(stderr, "error:%d: Method does not define return type, return type of '%s' present\n", lineno, s.c_str());
		error();
  }
	else if (return_value == NULL && calling_method->return_type == NULL) {
		return "Nothing";
	}

	else {
		fprintf(stderr, "error:%d: return statement must be of type '%s'\n", lineno, calling_method->return_type);
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
			fprintf(stderr, "error:%d : uninitalized variable '%s'\n", lineno, s.c_str() );
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
			fprintf(stderr, "error:%d : uninitalized field '%s'\n", lineno, s.c_str() );
			error();
			return "Nothing";
		}
	}

return "Nothing";
}

string assign_node::type_checks( map< string, string > *local, map< string, string > *field )
{

	// var case
	if (lhs->var != NULL) {
		string s1 = string(lhs->var);

		var_name = s1;
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

	vector<r_expr_node *>::const_iterator iter;
	for (iter = arg_vector->begin(); iter != arg_vector->end(); ++iter) {
		(*iter)->type_checks(local, field);
	}

	string s(c_name);
	return s;
}

string method_call_node::type_checks( map< string, string > *local, map< string, string > *field ) 
{

	if (sweep == 2) {

		string s1 = instance->type_checks(local, field);

		method_node *AST_method_node = get_AST_method_node (s1, string(modifier) ); 

		if (AST_method_node == NULL) {
			fprintf(stderr, "error:%d: Method '%s' not found in class '%s'\n", lineno, modifier, s1.c_str());
			error();
			return "Nothing";
		}

		// check arg_vector (vector r_expr_node*)  against AST_method_node->formal_args (vector f_arg_pair*)
		vector<r_expr_node *>::const_iterator iter;

		//check1: length of arg vector  vs length of foraml args
		if( arg_vector->size() != AST_method_node->formal_args->size() )
		{
		  if (AST_method_node->lineno)
			fprintf(stderr,"error:%d Incorrect number of arguments for Method  \"%s\" defined at line:%d\n",lineno, AST_method_node->method_name, AST_method_node->lineno);
		  else
			fprintf(stderr,"error:%d Incorrect number of arguments for Method \"%s\" from default class\n",lineno, AST_method_node->method_name); 
			error();
			return "Nothing";
		}
		int i;	
		for (iter = arg_vector->begin(),i=0; iter != arg_vector->end(); ++iter, ++i) {
			string arg_type = (*iter)->type_checks(local, field);
			string formal_arg_type = (*AST_method_node->formal_args)[i]->return_type;

			if( !is_subclass(arg_type, formal_arg_type) )
			{
				fprintf(stderr,"error:%d: argument %d of type %s does not match formal argument of type %s in method %s\n",
						lineno,  (int) (arg_vector->size() - i - 1), arg_type.c_str(), formal_arg_type.c_str(), AST_method_node->method_name);
				error();
			}

		}

		// should be return type of method
		return string(AST_method_node->return_type);
	}

	return "Dummy";
}

string int_node::type_checks( map< string, string > *local, map< string, string > *field ) 
{
	return "Int";
}

string str_node::type_checks( map< string, string > *local, map< string, string > *field ) 
{
	return "String";
}
