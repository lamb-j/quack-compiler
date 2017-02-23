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

  void yyerror(const char *msg)
  {
        fprintf(stderr, "%d: %s (at '%s')\n", yylineno, msg, yytext);
  }

%}

%x mlcomment
%x slcomment
%x string1
%x string2

%%

"class"         { return CLASS; }
"def"           { return DEF; }
"extends"       { return EXTENDS; }
"if"            { return  IF; }
"elif"          { return  ELIF; }
"else"          { return  ELSE; }
"while"         { return  WHILE; }
"return"        { return  RETURN; }
">="            { return  ATLEAST; }
"<="            { return  ATMOST; }
"=="            { return  EQUALS; }
"and"           { return  AND; }
"or"            { return  OR; }
"not"           { return  NOT; }

[a-zA-Z_][a-zA-Z0-9_]*       {  yylval.strval = strdup(yytext);  return IDENT; }
[0-9]+                       {  yylval.intval = atoi(yytext);  return INT_LIT; }

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

\n        
[ \t]     { /* ignore whitespace */ }
"//".*    { /* ignore comments */ }
.         { yyerror("mystery character"); }
%%


/* No main program here */

