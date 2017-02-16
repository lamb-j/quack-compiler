/* quack parser */

%{
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>
#include <string.h>
#include "quack.h"
#include "class_tree.h"
#include  <algorithm>

extern vector < string > class_names;
list <tree_node *> *tree_list;

extern FILE *yyin;

program_node *root;

int yylex();
void yyerror(const char *s);

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

Program: Classes Statements { $$ = new program_node($1, $2); root = $$; }

Classes: /* empty */ { $$ = new list<class_node *>(); }
					| Classes Class { $$ = $1; $1->push_back($2); }

Class: Class_Signature Class_Body {$$ = new class_node($1, $2); }

Class_Signature : CLASS IDENT '(' Formal_Args ')' { $$ = new class_sig_node($2, $4, "Obj");
																									class_names.push_back( $2 ); }
                | CLASS IDENT '(' Formal_Args ')' EXTENDS IDENT { $$ = new class_sig_node($2, $4, $7);  
																									class_names.push_back( $2 ); }

Class_Body: '{' Statements Methods '}' { $$ = new class_body_node( $2, $3 ); }

Methods: /* empty */ { $$ = new list<method_node *>(); }
					| Methods Method { $$ = $1; $1 -> push_back($2); }

Method: DEF IDENT '(' Formal_Args ')' Statement_Block { $$ = new method_node($2, $4, NULL, $6); }
      | DEF IDENT '(' Formal_Args ')' ':' IDENT Statement_Block { $$ = new method_node($2, $4, $7, $8); }

Formal_Args: /* empty */ {$$ = new vector< f_arg_pair * >(); }
    | IDENT ':' IDENT Formal_Args { $$ = $4; $4 -> push_back( new f_arg_pair($1, $3) ); }
		| IDENT ':' IDENT ',' Formal_Args { $$ = $5; $5 -> push_back( new f_arg_pair($1, $3) ); }

Statement_Block: '{' Statements '}' { $$ = new statement_block_node($2); }

Statements: /* empty */ { $$ = new list<statement_node *>(); }
					| Statements Statement {$$ = $1; $1 -> push_back($2); }

Statement: RETURN R_Expr ';' { $$ = new return_node($2); }
         | RETURN ';' { $$ = new return_node( NULL ); }

Statement: IF R_Expr Statement_Block Elseif 
             { $$ = new if_node($2, $3, $4); }
         | IF R_Expr Statement_Block Elseif ELSE Statement_Block
             { $$ = new if_node($2, $3, $4, $6); }

Elseif: /* empty */ { $$ = new elif_data(); }
      | Elseif ELIF R_Expr Statement_Block { $$ = $1; $1 -> add($3, $4); }

Statement: WHILE R_Expr Statement_Block { $$ = new while_node($2, $3); }
			     
Statement: L_Expr '=' R_Expr ';' {$$ = new asgn_node($1,$3); }
         | L_Expr ':' IDENT '=' R_Expr ';' { $$ = new asgn_node($1, $3, $5); }

Statement: R_Expr ';' { $$ = $1; }

L_Expr: IDENT { $$ = new l_expr_node($1); }
			| R_Expr '.' IDENT { $$ = new l_expr_node($1, $3); } 

R_Expr: L_Expr {$$ = $1;}

R_Expr: R_Expr '.' IDENT '(' Actual_Args ')' { $$ = new method_call_node($1, $3, $5); }

R_Expr: IDENT '(' Actual_Args ')' { $$ = new constructor_call_node($1, $3); }
	
// NEEDS SOME WORK (accepts no commas, introduces 2 shift/reduce errors)
Actual_Args: /* empty */ { $$ = new list<r_expr_node *>(); }
           | R_Expr Actual_Args { $$ = $2; $2 -> push_back($1); } 
					 | R_Expr ',' Actual_Args { $$ = $3; $3 -> push_back($1); }

R_Expr: R_Expr '>' R_Expr { $$ = new compare_node($1, ">", $3) ;} 
      | R_Expr '<' R_Expr { $$ = new compare_node($1, "<" , $3); }
			| R_Expr EQUALS R_Expr { $$ = new compare_node($1, "==", $3); }
      | R_Expr ATLEAST R_Expr { $$ = new compare_node($1, ">=" , $3); }
      | R_Expr ATMOST R_Expr { $$ = new compare_node($1, "<=" , $3); }
      | R_Expr AND R_Expr { $$ = new compare_node($1,"AND" , $3); }
      | R_Expr OR R_Expr { $$ = new compare_node($1, "OR" , $3); }
      | NOT R_Expr {$$ = new unary_node( "NOT", $2) ; } 
 //     | '-' R_Expr %prec NEG { $$ = new unary_node( "-", $2) ;}

R_Expr: '(' R_Expr ')' { $$ = $2; }
      | R_Expr '+' R_Expr { $$ = new plus_node($1, $3); }
      | R_Expr '-' R_Expr { $$ = new minus_node($1, $3); }
      | R_Expr '*' R_Expr { $$ = new times_node($1, $3); }
      | R_Expr '/' R_Expr { $$ = new divide_node($1, $3); }


R_Expr: INT_LIT { $$ = new int_node($1); }
      //| IDENT { $$ = new str_node($1); }
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

	// check class names for Obj, ...

	class_names.push_back("Obj");
	class_names.push_back("Int");
	class_names.push_back("String");
	class_names.push_back("Nothing");
	class_names.push_back("Boolean");

        	
	printf("--- Evaluate ---\n");
	//sorting vector to check for duplicates
	sort( class_names.begin(), class_names.end() );
  	
	for( int i=1; i < class_names.size(); i++ )
	{
		if ( class_names[i].compare(class_names[i-1] ) == 0) 
		{
			fprintf(stderr,"error: duplicate class name %s\n",class_names[i].c_str());
		} 
	}  


	//adding default tree nodes to tree list

	tree_node *Obj = new tree_node("Obj");
	tree_node *Int = new tree_node("Int");
	tree_node *String = new tree_node("String");
	tree_node *Nothing = new tree_node("Nothing");
	tree_node *Boolean = new tree_node("Boolean");

	tree_list = new list <tree_node*>(); 

	tree_list->push_back(Obj);
	tree_list->push_back(Int);
	tree_list->push_back(String);
	tree_list->push_back(Boolean);
	tree_list->push_back(Nothing);

	Obj->children.push_back(Int);
	Obj->children.push_back(String);
	Obj->children.push_back(Nothing);
	Obj->children.push_back(Boolean);

	Int->parent = Obj;
	String->parent = Obj;
	Nothing->parent = Obj;
	Boolean->parent = Obj;
	
	if (root != NULL) root->evaluate();
	printf("\n");

	printf("--- Class Tree ---\n");
	print_tree(Obj, 0);
	printf("\n");

	printf("--- Syntax Tree ---\n");
	if (root != NULL) root->print(0);



}
