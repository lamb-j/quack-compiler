/* quack parser */

%{
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>
#include <string.h>
#include "quack.h"

statement_block_node *root;

int yylex();
void yyerror(const char *s);

%}

%union {
  int intval;
	char *strval;
	r_expr_node							*reNode;
	l_expr_node							*leNode;
	statement_node					*sNode;
	statement_block_node		*sbNode;
	list<statement_node *>	*sNode_list;
	list<r_expr_node *>			*argNode_list;
  elif_data								*elifNode;  
}

%type<argNode_list> Actual_Args;
%type<sbNode> Statement_Block;
%type<sNode> Statement;
%type<sNode_list> Statements;
%type<reNode> R_expr;
%type<leNode> L_expr;
%type<elifNode> Elseif;

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
%left NEG
%left '+' '-'
%left '*' '/'
%left '.'

%%

//Program: Classes Statements

//Classes: /* empty */
//					| Classes Class

//Class: Class_Signature Class_Body 

//Class_Signature : CLASS IDENT '(' Formal_Args ')' 
//                | CLASS IDENT '(' Formal_Args ')' EXTENDS IDENT

//Class_Body: '{' Statements Methods '}'

//Methods: /* empty */
//					| Methods Method

//Method: DEF IDENT '(' Formal_Args ')' Statement_Block
//      | DEF IDENT '(' Formal_Args ')' ':' IDENT Statement_Block

//Formal_Args: /* empty */
//    | IDENT ':' IDENT
//		| IDENT ':' IDENT ',' Formal_Args
		
Statement_Block: '{' Statements '}' { $$ = new statement_block_node($2); root = $$; }

Statements: /* empty */ { $$ = new list<statement_node *>(); }
					| Statements Statement {$$ = $1; $1 -> push_back($2); }

Statement: RETURN R_expr ';' { $$ = new return_node($2); }
         | RETURN ';' { $$ = new return_node( NULL ); }

Statement: IF R_expr Statement_Block Elseif 
             { $$ = new if_node($2, $3, $4); }
         | IF R_expr Statement_Block Elseif ELSE Statement_Block
             { $$ = new if_node($2, $3, $4, $6); }

Elseif: /* empty */ { $$ = new elif_data(); }
      | Elseif ELIF R_expr Statement_Block { $$ = $1; $1 -> add($3, $4); }

Statement: WHILE R_expr Statement_Block { $$ = new while_node($2, $3); }
			     
Statement: L_expr '=' R_expr ';' {$$ = new asgn_node($1,$3); }
         | L_expr ':' IDENT '=' R_expr ';' { $$ = new asgn_node($1, $3, $5); }

Statement: R_expr ';' { $$ = $1; }

L_expr: IDENT { $$ = new l_expr_node($1); }
			| R_expr '.' IDENT { $$ = new l_expr_node($1, $3); } 

R_expr: L_expr {$$ = $1;}

R_expr: R_expr '.' IDENT '(' Actual_Args ')' { $$ = new method_call_node($1, $3, $5); }

R_expr: IDENT '(' Actual_Args ')' { $$ = new constructor_call_node($1, $3); }
	
// NEEDS SOME WORK
Actual_Args: /* empty */ { $$ = new list<r_expr_node *>(); }
           | R_expr Actual_Args { $$ = $2; $2 -> push_back($1); } 
					 | R_expr ',' Actual_Args { $$ = $3; $3 -> push_back($1); }

//Statements: /* empty */ { $$ = new list<statement_node *>(); }
//					| Statements Statement {$$ = $1; $1 -> push_back($2); }

//R_expr: R_expr '>' R_expr 
//      | R_expr '<' R_expr 
//			| R_expr EQUALS R_expr 
//      | R_expr ATLEAST R_expr 
//      | R_expr ATMOST R_expr 
//      | R_expr AND R_expr 
//      | R_expr OR R_expr 
//      | NOT R_expr 
//      | '-' R_expr %prec NEG

R_expr: '(' R_expr ')' { $$ = $2; }
      | R_expr '+' R_expr { $$ = new plus_node($1, $3); }
      | R_expr '-' R_expr { $$ = new minus_node($1, $3); }
//      | R_expr '*' R_expr 
//      | R_expr '/' R_expr 


R_expr: INT_LIT { $$ = new int_node($1); }
      //| IDENT { $$ = new str_node($1); }
			| STRING_LIT { $$ = new str_node($1); }
  		| TRI_STRING_LIT { $$ = new str_node($1); }

%%

/* main program here */
int main (int argc, char **argv) 
{
  //FILE *yyin;
	//if (argc < 2) {
	//	printf("usage: scanner inputfile\n");
	//	exit(0);
	//}
	//yyin = fopen(argv[1], "r");

	//if (yyin == NULL) {
	//	printf("Bad file name: %s\n", argv[1]);
	//	exit(0);
	//}

	//yyrestart(f);

	int condition = yyparse();

	printf("Finished parse with result %d\n", condition);
	if (root != NULL) root->evaluate();
}
