/* quack parser */
%{
#include <stdio.h>
#include <stdlib.h>
#include "quack.tab.h"

int yylex();
void yyerror();
FILE *yyin;
%}

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
%token IDENT
%token INT_LIT
%token STRING_LIT
%token TRI_STRING_LIT

%left '.'
%left AND OR NOT
%left '<' '>'  EQUALS ATMOST ATLEAST
%left '+' '-'
%left '*' '/'

%%

Program: Classes Statements

Classes: /* empty */
					| Classes Class

Class: Class_Signature Class_Body 

Class_Signature : CLASS IDENT '(' Args ')' 
                | CLASS IDENT '(' Args ')' EXTENDS IDENT

Class_Body: '{' Statements Methods '}'

Methods: /* empty */
					| Methods Method

Method: DEF IDENT '(' Args ')' Statement_Block
      | DEF IDENT '(' Args ')' ':' IDENT Statement_Block

Args: /* empty */
    | IDENT ':' IDENT
		| IDENT ':' IDENT ',' Args
		
Statement_Block: '{' Statements '}' 

Statements: /* empty */
					| Statements Statement

Statement: RETURN R_expr ';'
         | RETURN ';'

Statement: IF R_expr Statement_Block Elseif
         | IF R_expr Statement_Block Elseif ELSE Statement_Block

Elseif: /* empty */
      | Elseif ELIF R_expr Statement_Block

Statement: WHILE R_expr Statement_Block
			     
Statement: L_expr '=' R_expr ';'
         | L_expr ':' IDENT '=' R_expr ';'

L_expr: IDENT
			| R_expr '.' IDENT  /** causes shift/reduce conflicts **/

Statement: R_expr ';'

R_expr: R_expr '.' IDENT '(' Actual_args ')'  /* had R_expr ',' IDENT */
      | IDENT '(' Actual_args ')'
	
Actual_args: /* empty */
           | R_expr
					 | R_expr ',' Actual_args

R_expr: L_expr

R_expr: '(' R_expr ')'
      | R_expr '+' R_expr 
      | R_expr '-' R_expr 
      | R_expr '*' R_expr 
      | R_expr '/' R_expr 

R_expr: R_expr '>' R_expr 
      | R_expr '<' R_expr 
			| R_expr EQUALS R_expr 
      | R_expr ATLEAST R_expr 
      | R_expr ATMOST R_expr 
      | R_expr AND R_expr 
      | R_expr OR R_expr 
      | NOT R_expr 

R_expr: INT_LIT 
      | STRING_LIT 
      | TRI_STRING_LIT 

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

}
