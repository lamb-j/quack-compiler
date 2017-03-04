#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <list>

using namespace std;

class tree_node;

void error();
// class defintions
class statement_node {
	public:
		virtual void print(int indent) = 0;
		virtual int build_classTree() = 0;
		virtual string type_checks( map< string, string > *local, map< string, string > *fields ) = 0;
};

class statement_block_node {
	protected:
		list <statement_node *> *statements;
	public:
		statement_block_node(list <statement_node *> *stmts);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
		void print(int indent);
};

class f_arg_pair {
	public:
		const char *name;
		const char *return_type;

		f_arg_pair(const char *n, const char *r) {name = n; return_type = r;}
}; 

class class_sig_node {
	public:
		const char *class_name;
		vector <f_arg_pair *> *formal_args;
		const char *parent;
		int lineno;

		class_sig_node(const char *c_name, vector <f_arg_pair *> *f_args, const char *p, int linenum);

		void print(int indent);
		tree_node * build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
};

class method_node {
	public:
		const char *method_name;
		vector < f_arg_pair *> *formal_args;
		const char *return_type;
		statement_block_node *body;
		int lineno;	

		// map method_var_table

		map <string, string> *meth_var_table;
		//map <string, string> *meth_arg_table;
		
		method_node(const char *name, vector < f_arg_pair * > *args, const char *r_type, statement_block_node *b, int linenum);

		void print(int indent);
		int build_classTree(tree_node *);

		string type_checks( map< string, string > *local, map< string, string > *fields );
};

class class_body_node{
	public:
		list<statement_node *> *statement_list;
		list<method_node *> *method_list;

		class_body_node(list<statement_node *> *s_list, list< method_node *> *m_list);

		void print(int indent);
		int build_classTree(tree_node *);

		string type_checks( map< string, string > *local, map< string, string > *fields );
};

class class_node {
	public:
		class_sig_node *sig;
		class_body_node *body;
		tree_node * class_tree_node;
		int lineno;

		class_node(class_sig_node *s, class_body_node *b, int linenum);

		// class var table
		map< string, string> *field_var_table;
		map< string, string> *local_var_table;
		

		void print(int indent);
		int build_classTree();

		string type_checks( map< string, string > *local, map< string, string > *fields );
};

class program_node {
	public:
		list <class_node *> *class_list;
		list <statement_node *> *statement_list;

		program_node(list <class_node *> *c, list <statement_node *> *s);


		// map st_var_table
		map <string, string> *stmt_var_table;
		
		void print(int indent);
		tree_node * build_classTree();
		string type_checks(tree_node *root);
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

		int lineno;

		l_expr_node(char *str, int linenum);
		l_expr_node(r_expr_node *r_node, char* str, int linenum);
		void print(int indent);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );

};

class while_node : public statement_node {
	public:
		r_expr_node *condition;
		statement_block_node *body;
		int lineno;	
		while_node(r_expr_node *cond, statement_block_node *stmts, int linenum);

		void print(int indent);
		int build_classTree();

		string type_checks( map< string, string > *local, map< string, string > *fields );
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
		int lineno;
		// else if
		elif_data *elif_pairs;

		// else
		statement_block_node *else_body;

		if_node(
				r_expr_node *if_c, 
				statement_block_node *if_b, 
				elif_data *elif_p, int linenum);
		if_node(
				r_expr_node *if_c, 
				statement_block_node *if_b, 
				elif_data *elif_p, 
				statement_block_node *else_b, int linenum); 

		void print(int indent);
		int build_classTree();

		string type_checks( map< string, string > *local, map< string, string > *fields );
};

class return_node : public statement_node {
	public:
		r_expr_node *return_value;

		return_node(r_expr_node *rv, int linenum);
		void print(int indent);


		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
		int lineno;
};

class assign_node : public statement_node {
	public:
		r_expr_node *rhs;
		l_expr_node *lhs;
		char *c_name;
		int lineno;

		assign_node(l_expr_node *left, r_expr_node *right, int linenum);
		assign_node(l_expr_node *left, char* str, r_expr_node *right, int linenum);

		void print(int indent);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
};

class constructor_call_node : public r_expr_node {
	public:
		char *c_name;
		list <r_expr_node *> *arg_list;
		int lineno;

		constructor_call_node(char *str, list <r_expr_node *> *args, int linenum);
		void print(int indent);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
};

class method_call_node : public r_expr_node {
	public:
		r_expr_node *instance;
		const char *modifier;
		list <r_expr_node *> *arg_list;
		int lineno;


		method_call_node(r_expr_node *ins, const char *mod, list <r_expr_node *> *args, int linenum);
		void print(int indent);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
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
		int lineno;
		unary_node(const char* sym, r_expr_node *R, int linenum);

		void print(int indent);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
};


class plus_node : public operator_node {
	public:
		int lineno;
		plus_node(r_expr_node *L, r_expr_node *R, int linenum);
		void print(int indent);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
};

class minus_node : public operator_node {
	public: 
		int lineno;
		minus_node(r_expr_node *L, r_expr_node *R, int linenum);
		void print(int indent);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
};

class times_node : public operator_node {
	public: 
		int lineno;		
		times_node(r_expr_node *L, r_expr_node *R, int linenum);
		void print(int indent);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
};

//class divide_node : public operator_node {
//	public: 
//		int lineno;		
//		divide_node(r_expr_node *L, r_expr_node *R, int linenum);
//		void print(int indent);
//		int build_classTree();
//		string type_checks( map< string, string > *local, map< string, string > *fields );
//};

class compare_node : public operator_node {
	public:
		compare_node(r_expr_node *L, const char* sym, r_expr_node *R, int linenum);
		int lineno;
		void print(int indent);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
};

class int_node : public r_expr_node {
	public:
		int_node(int value);
		void print(int indent);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
};

// inhereit from l_expr_node?
class str_node : public r_expr_node {
	public:
		str_node(char *value);
		void print(int indent);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
};

// Class Tree Functions
class tree_node {
	public:
		string name;

	  class_node *AST_node;

		tree_node *parent;
		vector <tree_node *> children;

		vector <string > method_names;
		
		// add methods/arguments

    tree_node(string n) { name = n ; }
};

int print_tree( tree_node *root, int level );
tree_node * append_tree( list <tree_node *> *tree_list, string parent_class, string new_class);
tree_node * get_tree_node(list < tree_node *> *tree_node_list, string cname);
int class_defines_method(tree_node * class_node, string method_name);
//tree_node * least_common_ancestor(tree_node *A, tree_node *B);
string least_common_ancestor(string A, string B);

class_node * get_AST_class_node(string class_name);
method_node * get_AST_method_node(string class_name, string method_name);

int is_subclass(string sub_class, string super_class);
int is_superclass(string super_class, string sub_class);


// add parent methods

void add_parent_methods(list <method_node *> *parent_mlist, list <method_node *> *child_mlist, string child_class);
void add_parent_fields( map <string, string> *parent_fields, map <string, string > *child_fields);

void type_check_class(tree_node *root);
