/* recognize tokens for the calculator and print them out */
/* Try to add badstring test things */
%option yylineno
%{
  #include <string>
  #include "quack.h"
  #include "y.tab.h"
  #include  <stdlib.h>
  #include  <stdio.h>
  #include  <iostream>

  int lineno =1;
  void yyerror(const char *msg)
  {
        fprintf(stderr, "%d: %s (at '%s')\n", yylineno, msg, yytext);
				error();
  }

  void report_error(const char *msg, int lineno)
  {
        fprintf(stderr, "%d: %s\n", lineno, msg);
  }

%}

%x mlcomment
%x slcomment
%x string1
%x string2

%%

"class"         { yylloc.first_line = yylineno; return CLASS; }
"def"           { yylloc.first_line = yylineno; return DEF; }
"extends"       { yylloc.first_line = yylineno; return EXTENDS; }
"if"            { yylloc.first_line = yylineno; return  IF; }
"elif"          { yylloc.first_line = yylineno; return  ELIF; }
"else"          { yylloc.first_line = yylineno; return  ELSE; }
"while"         { yylloc.first_line = yylineno; return  WHILE; }
"return"        { yylloc.first_line = yylineno; return  RETURN; }
">="            { yylloc.first_line = yylineno; return  ATLEAST; }
"<="            { yylloc.first_line = yylineno; return  ATMOST; }
"=="            { yylloc.first_line = yylineno; return  EQUALS; }
"and"           { yylloc.first_line = yylineno; return  AND; }
"or"            { yylloc.first_line = yylineno; return  OR; }
"not"           { yylloc.first_line = yylineno; return  NOT; }

[a-zA-Z_][a-zA-Z0-9_]*       { yylloc.first_line = yylineno;  yylval.strval = strdup(yytext);  return IDENT; }
[0-9]+                       { yylloc.first_line = yylineno;  yylval.intval = atoi(yytext);  return INT_LIT; }

[+]       { yylloc.first_line = yylineno; return '+'; }
"-"       { yylloc.first_line = yylineno; return '-'; }
"*"       { yylloc.first_line = yylineno; return '*'; }
"/"       { yylloc.first_line = yylineno; return '/'; }
"="       { yylloc.first_line = yylineno; return '='; }
">"       { yylloc.first_line = yylineno; return '>'; }
"<"       { yylloc.first_line = yylineno; return '<'; }
"."       { yylloc.first_line = yylineno; return '.'; }
","       { yylloc.first_line = yylineno; return ','; }
":"       { yylloc.first_line = yylineno; return ':'; }
";"       { yylloc.first_line = yylineno; return ';'; }
"("       { yylloc.first_line = yylineno; return '('; }
")"       { yylloc.first_line = yylineno; return ')'; }
"{" 	  { yylloc.first_line = yylineno; return '{'; }
"}"       { yylloc.first_line = yylineno; return '}'; }


"/*"                      BEGIN(mlcomment);
<mlcomment><<EOF>>        { yyerror("Multiline has been started but has not been ended at end of the file."); 
														BEGIN(INITIAL);}
<mlcomment>[^*\n]*        /* eat anything that's not a '*' */
<mlcomment>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
<mlcomment>[\n]*          
<mlcomment>"*"+"/"        BEGIN(INITIAL);

"//"                      BEGIN(slcomment);
<slcomment>[^\n]          
<slcomment>[\n]           


"\"\"\""                  { BEGIN(string2);}
<string2>[\n]              
<string2>^["]["]["]
<string2><<EOF>>          { yyerror("incorrect end for triple-quoted string"); 
														BEGIN(INITIAL); return STRING_LIT;}
<string2>"\"\"\""         { BEGIN(INITIAL); return STRING_LIT; }

["]                       { BEGIN(string1); }
<string1>[\\][0btnrf"\\]  
<string1>[\\][^0btnrf"\\] { yyerror(" illegal escape code"); return STRING_LIT;}
<string1>[\n]             { yyerror("Multiline string is not permitted for single qoute" ); 
														BEGIN(INITIAL); return STRING_LIT; }
<string1><<EOF>>          { BEGIN(INITIAL); return STRING_LIT;}
<string1>[^"]             
<string1>["]              { BEGIN(INITIAL); return STRING_LIT; }

[\n]	  
[ \t]     { /* ignore whitespace */ }
"//".*    { /* ignore comments */ }
.         { yyerror("mystery character"); }
%%


/* No main program here */

