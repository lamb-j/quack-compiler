/* recognize tokens for the calculator and print them out */
/* Try to add badstring test things */
%option yylineno
%{
  #include "quack.tab.h"

	void yyerror(const char *msg) {
	  fprintf(stderr, "%d: %s (at '%s')\n", yylineno, msg, yytext);
	}

%}

%%
"class"   { return CLASS; }
"def"			{ return DEF; }
"extends" { return EXTENDS; }
"if"			{ return  IF; }
"elif"		{ return  ELIF; }
"else"		{ return  ELSE; }
"while"		{ return  WHILE; }
"return"	{ return  RETURN; }
">="			{ return  ATLEAST; }
"<="			{ return  ATMOST; }
"=="			{ return  EQUALS; }
"and"			{ return  AND; }
"or"			{ return  OR; }
"not"			{ return  NOT; }

[a-zA-Z_][a-zA-Z0-9_]*       {  return IDENT; }
[0-9]+                       {  return INT_LIT; } 
\"([^"\\]|\\[0btnrf"\\])*\"  {  return STRING_LIT; }
["]["]["](.|\n)*["]["]["]    {  return TRI_STRING_LIT; }


[+]       { return '+'; }
"-"       { return '-'; }
"*"       { return '*'; }
"/"       { return '/'; }
"="       { return '='; }
">"       { return '>'; }
"<"       { return '<'; }
"."       { return '.'; }
","       { return ','; }
":"       { return ':'; }
";"       { return ';'; }
"("       { return '('; }
")"       { return ')'; }
"{"       { return '{'; }
"}"       { return '}'; }

\n        { /* ignore newline */ }
[ \t]     { /* ignore whitespace */ }
"//".*    { /* ignore comments */ }
\/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+\/ { /* ignore block comments */ }
.         { fprintf(stderr, "BAD: Mystery character %c\n", *yytext); exit(0); }
%%

/* No main program here */
