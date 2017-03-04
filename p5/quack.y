/* quack parser */

%{
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>
#include <string.h>
#include "quack.h"
#include  <algorithm>

// external data structures
extern vector < string > class_names;
list <tree_node *> *tree_list;
extern int error_flag;

extern FILE *yyin;

program_node *AST_root;

int yylex();
void yyerror(const char *s);
extern int yylineno;

int sweep;

%}

%union {
	int intval;
	char *strval;

	r_expr_node			*reNode;
	l_expr_node			*leNode;

	program_node						*pNode;

	class_node							*cNode;
	class_sig_node					*csNode;
	class_body_node					*cbNode;
	list<class_node *>			*cNode_list;

	statement_node					*sNode;
	statement_block_node		*sbNode;
	list<statement_node *>	*sNode_list;
	list<method_node *>			*mNode_list;
	method_node							*mNode;
	vector < f_arg_pair * >	*f_arg_vector;

	list<r_expr_node *>			*argNode_list;
	elif_data								*elifNode;  
}

%type<pNode> Program;

%type<cNode_list> Classes;
%type<cNode> Class;
%type<cbNode> Class_Body;
%type<csNode> Class_Signature;

%type<sbNode> Statement_Block;
%type<sNode> Statement;
%type<sNode_list> Statements;

%type<mNode_list> Methods;
%type<mNode> Method;
%type<f_arg_vector> Formal_Args;

%type<reNode> R_Expr;
%type<leNode> L_Expr;

%type<elifNode> Elseif;

%type<argNode_list> Actual_Args;

/* declare tokens */
%token CLASS
%token DEF
%token EXTENDS
%token IF
%token ELIF
%token ELSE
%token WHILE
%token RETURN
%token ATLEAST
%token ATMOST
%token EQUALS
%token AND
%token OR
%token NOT
%token <strval> IDENT
%token <intval> INT_LIT
%token <strval> STRING_LIT
%token <strval> TRI_STRING_LIT

%left AND OR NOT
%left '<' '>'  EQUALS ATMOST ATLEAST
%left '+' '-'
%left '*' '/'
%left NEG
%left '.'

%%

Program: Classes Statements { $$ = new program_node($1, $2); AST_root = $$; }

Classes: /* empty */ { $$ = new list<class_node *>(); }
| Classes Class { $$ = $1; $1->push_back($2); }

Class: Class_Signature Class_Body {$$ = new class_node($1, $2, @1.first_line); }

Class_Signature : CLASS IDENT '(' Formal_Args ')' { $$ = new class_sig_node($2, $4, "Obj", @1.first_line);								class_names.push_back( $2 ); }
| CLASS IDENT '(' Formal_Args ')' EXTENDS IDENT { $$ = new class_sig_node($2, $4, $7, @1.first_line);  
	class_names.push_back( $2 ); }

Class_Body: '{' Statements Methods '}' { $$ = new class_body_node( $2, $3 ); }

Methods: /* empty */ { $$ = new list<method_node *>(); }
| Methods Method { $$ = $1; $1 -> push_back($2); }

Method: DEF IDENT '(' Formal_Args ')' Statement_Block { $$ = new method_node($2, $4, "Nothing", $6, @1.first_line); }
| DEF IDENT '(' Formal_Args ')' ':' IDENT Statement_Block { $$ = new method_node($2, $4, $7, $8, @1.first_line); }

Formal_Args: /* empty */ {$$ = new vector< f_arg_pair * >(); }
| IDENT ':' IDENT Formal_Args { $$ = $4; $4 -> push_back( new f_arg_pair($1, $3) ); }
| IDENT ':' IDENT ',' Formal_Args { $$ = $5; $5 -> push_back( new f_arg_pair($1, $3) ); }

Statement_Block: '{' Statements '}' { $$ = new statement_block_node($2); }

Statements: /* empty */ { $$ = new list<statement_node *>(); }
| Statements Statement {$$ = $1; $1 -> push_back($2); }

Statement: RETURN R_Expr ';' { $$ = new return_node($2, @1.first_line); }
| RETURN ';' { $$ = new return_node( NULL, @1.first_line ); }

Statement: IF R_Expr Statement_Block Elseif 
{ $$ = new if_node($2, $3, $4, @1.first_line); }
| IF R_Expr Statement_Block Elseif ELSE Statement_Block
{ $$ = new if_node($2, $3, $4, $6, @1.first_line); }

Elseif: /* empty */ { $$ = new elif_data(); }
| Elseif ELIF R_Expr Statement_Block { $$ = $1; $1 -> add($3, $4); }

Statement: WHILE R_Expr Statement_Block { $$ = new while_node($2, $3, @1.first_line); }

Statement: L_Expr '=' R_Expr ';' { $$ = new assign_node($1,$3, @1.first_line); }
| L_Expr ':' IDENT '=' R_Expr ';' { $$ = new assign_node($1, $3, $5, @1.first_line); }

Statement: R_Expr ';' { $$ = $1; }

L_Expr: IDENT { $$ = new l_expr_node($1, @1.first_line); }
| R_Expr '.' IDENT { $$ = new l_expr_node($1, $3, @1.first_line); } 

R_Expr: L_Expr {$$ = $1;}

R_Expr: R_Expr '.' IDENT '(' Actual_Args ')' { $$ = new method_call_node($1, $3, $5, @1.first_line); }

R_Expr: IDENT '(' Actual_Args ')' { $$ = new constructor_call_node($1, $3, @1.first_line); }

// NEEDS SOME WORK (accepts no commas, introduces 2 shift/reduce errors)
Actual_Args: /* empty */ { $$ = new list<r_expr_node *>(); }
| R_Expr Actual_Args { $$ = $2; $2 -> push_back($1); } 
| R_Expr ',' Actual_Args { $$ = $3; $3 -> push_back($1); }

R_Expr: R_Expr '>' R_Expr {   list<r_expr_node *> *args = new list<r_expr_node *>();
			args->push_back($1);
			args->push_back($3);
			$$ = new method_call_node($1, "MORE", args, @1.first_line); 
}
| R_Expr '<' R_Expr {   list<r_expr_node *> *args = new list<r_expr_node *>();
			args->push_back($1);
			args->push_back($3);
			$$ = new method_call_node($1, "LESS", args, @1.first_line); 
}
| R_Expr EQUALS R_Expr {   list<r_expr_node *> *args = new list<r_expr_node *>();
			args->push_back($1);
			args->push_back($3);
			$$ = new method_call_node($1, "EQUALS", args, @1.first_line); 
}
| R_Expr ATLEAST R_Expr {   list<r_expr_node *> *args = new list<r_expr_node *>();
			args->push_back($1);
			args->push_back($3);
			$$ = new method_call_node($1, "ATLEAST", args, @1.first_line); 
}
| R_Expr ATMOST R_Expr {   list<r_expr_node *> *args = new list<r_expr_node *>();
			args->push_back($1);
			args->push_back($3);
			$$ = new method_call_node($1, "ATMOST", args, @1.first_line); 
}
| R_Expr AND R_Expr {   list<r_expr_node *> *args = new list<r_expr_node *>();
			args->push_back($1);
			args->push_back($3);
			$$ = new method_call_node($1, "AND", args, @1.first_line); 
}
| R_Expr OR R_Expr {   list<r_expr_node *> *args = new list<r_expr_node *>();
			args->push_back($1);
			args->push_back($3);
			$$ = new method_call_node($1, "OR", args, @1.first_line); 
}
| NOT R_Expr {   list<r_expr_node *> *args = new list<r_expr_node *>();
			args->push_back($2);
			$$ = new method_call_node($2, "NOT", args, @1.first_line); 
}
// Introduces 19 shift-reduce errors
//| '-' R_Expr %prec NEG {   list<r_expr_node *> *args = new list<r_expr_node *>();
//			args->push_back($2);
//			$$ = new method_call_node($2, "NEG", args, @1.first_line); 
//}

R_Expr: '(' R_Expr ')' { $$ = $2; }
| R_Expr '+' R_Expr {   list<r_expr_node *> *args = new list<r_expr_node *>();
			args->push_back($1);
			args->push_back($3);
			$$ = new method_call_node($1, "PLUS", args, @1.first_line); 
}
| R_Expr '-' R_Expr {   list<r_expr_node *> *args = new list<r_expr_node *>();
			args->push_back($1);
			args->push_back($3);
			$$ = new method_call_node($1, "MINUS", args, @1.first_line); 
}
| R_Expr '*' R_Expr {   list<r_expr_node *> *args = new list<r_expr_node *>();
			args->push_back($1);
			args->push_back($3);
			$$ = new method_call_node($1, "TIMES", args, @1.first_line); 
}
| R_Expr '/' R_Expr {   list<r_expr_node *> *args = new list<r_expr_node *>();
			args->push_back($1);
			args->push_back($3);
			$$ = new method_call_node($1, "DIVIDE", args, @1.first_line); 
}

R_Expr: INT_LIT { $$ = new int_node($1); }
| STRING_LIT { $$ = new str_node($1); }
| TRI_STRING_LIT { $$ = new str_node($1); }

%%

/* main program here */
int main (int argc, char **argv) 
{
	if (argc < 2) {
		printf("usage: scanner inputfile\n");
		exit(0);
	}
	yyin = fopen(argv[1], "r");

	if (yyin == NULL) {
		printf("Bad file name: %s\n", argv[1]);
		exit(0);
	}

	//yyrestart(f);

	int condition = yyparse();

	printf("Finished parse with result %d\n", condition);

	if (condition) exit(0);

	if (AST_root != NULL)
	{
		printf("--- Class Errors ---\n");
		tree_node * class_root = AST_root->build_classTree();
		if (error_flag) return 0;
		printf("\n");

    // two sweeps
		printf("--- Type Check Errors ---\n");
		sweep = 1;
		AST_root->type_checks(class_root);
		if (error_flag) return 0;
		sweep = 2;
		AST_root->type_checks(class_root);
		if (error_flag) return 0;
		printf("\n");

    /*

		list<class_node *>::const_iterator c_iter;
		for (c_iter = AST_root->class_list->begin(); c_iter != AST_root->class_list->end(); ++c_iter) {
			class_node *c_node = (*c_iter);

			printf("--- Class %s Symbol Table ---\n", c_node->sig->class_name );
			for (auto iter = c_node->local_var_table->cbegin(); iter!= c_node->local_var_table->cend(); ++iter)
			{
				printf("  local:%s\ttype:%s\n",iter->first.c_str(), iter->second.c_str());
			}
			printf("\n");
			for (auto iter = c_node->field_var_table->cbegin(); iter!= c_node->field_var_table->cend(); ++iter)
			{
				printf("  field:%s\ttype:%s\n",iter->first.c_str(), iter->second.c_str());
			}
			printf("\n");
			
			//printing the method var table
			
			list<method_node *>::const_iterator m_iter;
			list<method_node *> *m_list_ptr = c_node->body->method_list; 
            
			for (m_iter = m_list_ptr->begin(); m_iter != m_list_ptr->end(); ++m_iter) {
				method_node *m_node = (*m_iter);
				
				
				printf("      --- Method %s Symbol Table ---\n", m_node->method_name );
				for (auto iter = m_node->meth_var_table->cbegin(); iter!= m_node->meth_var_table->cend(); ++iter)
				{
					printf("        local:%s\ttype:%s\n",iter->first.c_str(), iter->second.c_str());
				}
				printf("\n");
			}
			printf("\n");
		}

		printf("--- Statement Symbol Table ---\n");
		for (auto iter = AST_root->stmt_var_table->cbegin(); iter!= AST_root->stmt_var_table->cend(); ++iter)
		{
			printf("  var:%s\ttype:%s\n",iter->first.c_str(), iter->second.c_str());
		}
		printf("\n");
	*/

		printf("--- Class Tree ---\n");
		print_tree(class_root, 0);
		printf("\n");

		printf("--- Syntax Tree ---\n");
		AST_root->print(0);

	}

}
