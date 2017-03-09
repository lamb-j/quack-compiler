#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <vector>

using namespace std;

class tree_node;

void error();
// class defintions
class statement_node {
	public:
		virtual void print(int indent) = 0;
		virtual int build_classTree() = 0;
		virtual string type_checks( map< string, string > *local, map< string, string > *fields ) = 0;
    virtual string codegen() = 0;
};

class statement_block_node {
	protected:
		vector <statement_node *> *statements;
	public:
		statement_block_node(vector <statement_node *> *stmts);

		void print(int indent);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
    string codegen();
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
    string codegen();
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
    string codegen();
};

class class_body_node{
	public:
		vector<statement_node *> *statement_vector;
		vector<method_node *> *method_vector;

		class_body_node(vector<statement_node *> *s_vector, vector< method_node *> *m_vector);

		void print(int indent);
		int build_classTree(tree_node *);

		string type_checks( map< string, string > *local, map< string, string > *fields );
    string codegen();
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
    string codegen();
};

class program_node {
	public:
		vector <class_node *> *class_vector;
		vector <statement_node *> *statement_vector;

		program_node(vector <class_node *> *c, vector <statement_node *> *s);


		// map st_var_table
		map <string, string> *stmt_var_table;

		void print(int indent);
		tree_node * build_classTree();
		string type_checks(tree_node *root);
    string codegen(tree_node *root);
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
    string codegen();
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
    string codegen();
};

class elif_data {
	public:
		vector < r_expr_node *> *elif_conditions;
		vector < statement_block_node *> *elif_bodies;
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
    string codegen();
};

class return_node : public statement_node {
	public:
		r_expr_node *return_value;

		return_node(r_expr_node *rv, int linenum);
		int lineno;

		void print(int indent);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
    string codegen();
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
    string codegen();
};

class constructor_call_node : public r_expr_node {
	public:
		char *c_name;
		vector <r_expr_node *> *arg_vector;
		int lineno;

		constructor_call_node(char *str, vector <r_expr_node *> *args, int linenum);
		void print(int indent);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
    string codegen();
};

class method_call_node : public r_expr_node {
	public:
		r_expr_node *instance;
		const char *modifier;
		vector <r_expr_node *> *arg_vector;
		int lineno;


		method_call_node(r_expr_node *ins, const char *mod, vector <r_expr_node *> *args, int linenum);
		void print(int indent);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
    string codegen();
};

class plus_node: public r_expr_node {
	public:
		r_expr_node *left;
		r_expr_node *right;
		
		int lineno;
		plus_node(r_expr_node *L, r_expr_node *R, int linenum);
		void print(int indent);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
		string codegen();
};

class int_node : public r_expr_node {
	public:
		int_node(int value);
		void print(int indent);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
    string codegen();
};

class str_node : public r_expr_node {
	public:
		str_node(char *value);
		void print(int indent);
		int build_classTree();
		string type_checks( map< string, string > *local, map< string, string > *fields );
    string codegen();
};

// class tree functions
class tree_node {
	public:
		string name;

		class_node *AST_node;

		tree_node *parent;
		vector <tree_node *> children;

		vector <string > method_names;

		tree_node(string n) { name = n ; }
};

int print_tree( tree_node *root, int level );
tree_node * append_tree( vector <tree_node *> *tree_vector, string parent_class, string new_class);
tree_node * get_tree_node(vector < tree_node *> *tree_node_vector, string cname);
int class_defines_method(tree_node * class_node, string method_name);
string least_common_ancestor(string a, string b);

class_node * get_AST_class_node(string class_name);
method_node * get_AST_method_node(string class_name, string method_name);

int is_subclass(string sub_class, string super_class);
int is_superclass(string super_class, string sub_class);


// add parent methods

void add_parent_methods(vector <method_node *> *parent_mvector, vector <method_node *> *child_mvector, string child_class);
void add_parent_fields( map <string, string> *parent_fields, map <string, string > *child_fields);

void type_check_class(tree_node *root);
void codegen_class(tree_node *root);
