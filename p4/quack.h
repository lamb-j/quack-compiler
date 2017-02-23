#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <list>
#include "class_tree.h"

using namespace std;

class statement_node {
	public:
		virtual void print(int indent) = 0;
		virtual int build_classTree() = 0;
		virtual int static_checks() = 0;
		virtual string type_checks() = 0;
};

class statement_block_node {
	protected:
		list <statement_node *> *statements;
	public:
		statement_block_node(list <statement_node *> *stmts);
		int build_classTree();
		int static_checks();
		string type_checks();
		void print(int indent);
};

class f_arg_pair {
	public:
		char *name;
		char *return_type;

		f_arg_pair(char *n, char *r) {name = n; return_type = r;}
}; 

class class_sig_node {
	public:
		char *class_name;
	  vector <f_arg_pair *> *formal_args;
	  const char *parent;

		class_sig_node(char *c_name, vector <f_arg_pair *> *f_args, const char *p);

		void print(int indent);
		tree_node * build_classTree();
		int static_checks();
		string type_checks();
};

class method_node {
	public:
		char *method_name;
		vector < f_arg_pair *> *formal_args;
		char *return_type;
		statement_block_node *body;
		
		method_node(char *name, vector < f_arg_pair * > *args, char *r_type, statement_block_node *b);

		void print(int indent);
		int build_classTree(tree_node *);

		int static_checks();
		string type_checks();
};

class class_body_node{
	public:
		list<statement_node *> *statement_list;
		list<method_node *> *method_list;

		class_body_node(list<statement_node *> *s_list, list< method_node *> *m_list);

		void print(int indent);
		int build_classTree(tree_node *);

		int static_checks();
		string type_checks();
};

class class_node {
	public:
		class_sig_node *sig;
		class_body_node *body;

		class_node(class_sig_node *s, class_body_node *b);

		void print(int indent);
		int build_classTree();

		int static_checks();
		string type_checks();
};

class program_node {
	public:
		list <class_node *> *class_list;
		list <statement_node *> *statement_list;

	program_node(list <class_node *> *c, list <statement_node *> *s);

	void print(int indent);
	tree_node * build_classTree();
	int static_checks();
	string type_checks();
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
		void print(int indent);
		int build_classTree();
		int static_checks();
		string type_checks();
		
};

class while_node : public statement_node {
	public:
		r_expr_node *condition;
		statement_block_node *body;
	
    while_node(r_expr_node *cond, statement_block_node *stmts);

		void print(int indent);
		int build_classTree();

		int static_checks();
		string type_checks();
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

	void print(int indent);
	int build_classTree();

	int static_checks();
	string type_checks();
};

class return_node : public statement_node {
	public:
		return_node(r_expr_node *rv);
		void print(int indent);
		int build_classTree();
		int static_checks();
		string type_checks();

		r_expr_node *return_value;
};

class assign_node : public statement_node {
	public:
		r_expr_node *rhs;
		l_expr_node *lhs;
		char *c_name;

		assign_node(l_expr_node *left, r_expr_node *right);
		assign_node(l_expr_node *left, char* str, r_expr_node *right);
		
		void print(int indent);
		int build_classTree();
		int static_checks();
		string type_checks();
};

class constructor_call_node : public r_expr_node {
	public:
		char *c_name;
		list <r_expr_node *> *arg_list;

		constructor_call_node(char *str, list <r_expr_node *> *args);
		void print(int indent);
		int build_classTree();
		int static_checks();
		string type_checks();
};

class method_call_node : public r_expr_node {
	public:
		r_expr_node *instance;
		char *modifier;
		list <r_expr_node *> *arg_list;

		method_call_node(r_expr_node *ins, char *mod, list <r_expr_node *> *args);
		void print(int indent);
		int build_classTree();
		int static_checks();
		string type_checks();
};

class operator_node : public r_expr_node {
	public:
		r_expr_node *left;
		r_expr_node *right;
    const char* symbol;
		operator_node(r_expr_node *L, r_expr_node *R);
		operator_node(r_expr_node *L, const char* sym, r_expr_node *R);

};

class unary_node : public r_expr_node {
	public:
		r_expr_node *right;
		const char *symbol;

		unary_node(const char* sym, r_expr_node *R);

		void print(int indent);
		int build_classTree();
		int static_checks();
		string type_checks();
};


class plus_node : public operator_node {
	public:

		plus_node(r_expr_node *L, r_expr_node *R);
		void print(int indent);
		int build_classTree();
		int static_checks();
		string type_checks();
};

class minus_node : public operator_node {
	public:

		minus_node(r_expr_node *L, r_expr_node *R);
		void print(int indent);
		int build_classTree();
		int static_checks();
		string type_checks();
};

class times_node : public operator_node {
	public:
		
		times_node(r_expr_node *L, r_expr_node *R);
		void print(int indent);
		int build_classTree();
		int static_checks();
		string type_checks();
};

class divide_node : public operator_node {
	public:
		
		divide_node(r_expr_node *L, r_expr_node *R);
		void print(int indent);
		int build_classTree();
		int static_checks();
		string type_checks();
};

class compare_node : public operator_node {
	public:
		compare_node(r_expr_node *L, const char* sym, r_expr_node *R);
		void print(int indent);
		int build_classTree();
		int static_checks();
		string type_checks();
};

class int_node : public r_expr_node {
	public:
		int_node(int value);
		void print(int indent);
		int static_checks();
		int build_classTree();
		string type_checks();
};

// inhereit from l_expr_node?
class str_node : public r_expr_node {
	public:
		str_node(char *value);
		void print(int indent);
		int build_classTree();
		int static_checks();
		string type_checks();
};
