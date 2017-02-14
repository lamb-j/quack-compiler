#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>

using namespace std;

class statement_node {
	public:
		virtual void print() = 0;
		virtual int evaluate() = 0;
};

class statement_block_node {
	protected:
		list <statement_node *> *statements;
	public:
		statement_block_node(list <statement_node *> *stmts);
		int evaluate();
		void print();
};

class r_expr_node : public statement_node {
	public:
		int num;
		char *str;
};

class l_expr_node : public r_expr_node {
	public:
		char *var;
		char *modifier;
		r_expr_node *instance;
		
		l_expr_node(char *str);
		l_expr_node(r_expr_node *r_node, char* str);
		void print();
		int evaluate();
		
};

class while_node : public statement_node {
	public:
		r_expr_node *condition;
		statement_block_node *body;
	
    while_node(r_expr_node *cond, statement_block_node *stmts);

		void print();
		int evaluate();
};

class elif_data {
	public:
		list < r_expr_node *> *elif_conditions;
		list < statement_block_node *> *elif_bodies;
		int size;
	public:
		elif_data();

		void add(r_expr_node *new_cond, statement_block_node *new_body);
};

class if_node : public statement_node {
	public:

		// if 
		r_expr_node *if_condition;
		statement_block_node *if_body;

		// else if
		elif_data *elif_pairs;

		// else
		statement_block_node *else_body;

    if_node(
				r_expr_node *if_c, 
				statement_block_node *if_b, 
				elif_data *elif_p);
    if_node(
				r_expr_node *if_c, 
				statement_block_node *if_b, 
				elif_data *elif_p, 
				statement_block_node *else_b); 

	  void print();
		int evaluate();
};

class return_node : public statement_node {
	public:
		return_node(r_expr_node *rv);
		void print();
		int evaluate();

		r_expr_node *return_value;
};

class asgn_node : public statement_node {
	public:
		r_expr_node *rhs;
		l_expr_node *lhs;
		char *c_name;

		asgn_node(l_expr_node *left, r_expr_node *right);
		asgn_node(l_expr_node *left, char* str, r_expr_node *right);
		
		void print();
		int evaluate();
};

class constructor_call_node : public r_expr_node {
	public:
		char *c_name;
		list <r_expr_node *> *arg_list;

		constructor_call_node(char *str, list <r_expr_node *> *args);
		void print();
		int evaluate();
};

class method_call_node : public r_expr_node {
	public:
		r_expr_node *instance;
		char *modifier;
		list <r_expr_node *> *arg_list;

		method_call_node(r_expr_node *ins, char *mod, list <r_expr_node *> *args);
		void print();
		int evaluate();
};

class operator_node : public r_expr_node {
	public:
		r_expr_node *left;
		r_expr_node *right;

		operator_node(r_expr_node *L, r_expr_node *R);
};

class plus_node : public operator_node {
	public:

		plus_node(r_expr_node *L, r_expr_node *R);
		void print();
		int evaluate();
};

class minus_node : public operator_node {
	public:

		minus_node(r_expr_node *L, r_expr_node *R);
		void print();
		int evaluate();
};

class int_node : public r_expr_node {
	public:
		int_node(int value);
		void print();
		int evaluate();
};

class str_node : public r_expr_node {
	public:
		str_node(char *value);
		void print();
		int evaluate();
};
