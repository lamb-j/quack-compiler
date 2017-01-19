/* recognize tokens for the calculator and print them out */
%option yylineno
%{
  enum yytokentype {
	  CLASS = 258,
		DEF = 259,
		EXTENDS = 260,
		IF = 261,
		ELIF = 262,
		ELSE = 263,
		WHILE = 264,
		RETURN = 265,
		ATLEAST = 266,
		ATMOST = 267,
		EQUALS = 268,
		AND = 269,
		OR = 270,
		NOT = 271,
		IDENT = 272,
		INT_LIT = 273,
		STRING_LIT = 274,
		TRI_STRING_LIT = 275
  };

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

[a-zA-Z_][a-zA-Z0-9_]* { return IDENT; }
[0-9]+                 { return INT_LIT; } 
\"([^"\\]|\\[0btnrf"\\])*\"              { return STRING_LIT; }
["]["]["](.|\n)*["]["]["]  { return TRI_STRING_LIT; }

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
\n        { return '\n'; }

[ \t]     { /* ignore whitespace */ }
"//".*    { /* ignore comments */ }
\/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+\/ { /* ignore block comments */ }
.         { fprintf(stderr, "BAD: Mystery character %c\n", *yytext); exit(0); }
%%

int main (int argc, char **argv)
{
  int tok;
	int line_numb = 1;

  while (tok = yylex()) {
	  
		if (tok < 256) { 
			if (tok != '\n')
				//printf("%d  %c \"%s\"\n", line_numb, tok, yytext);
				printf("%d  %c \"%s\"\n", yylineno, tok, yytext);
    }

		else { 
			char *s;
			switch (tok)
			{
				case CLASS:				s = "CLASS";			break;
				case DEF:					s = "DEF";				break;
				case EXTENDS:			s = "EXTENDS";		break;
				case IF:					s = "IF";					break;
				case ELIF:				s = "ELIF";				break;
				case ELSE:				s = "ELSE";				break;
				case WHILE:				s = "WHILE";			break;
				case RETURN:			s = "RETURN";			break;
				case ATLEAST:			s = "ATLEAST";		break;
				case ATMOST:			s = "ATMOST";			break;
				case EQUALS:			s = "EQUALS";			break;
				case AND:					s = "AND";				break;
				case OR:					s = "OR";					break;
				case NOT:					s = "NOT";				break;
				case IDENT:				s = "IDENT";			break;
				case INT_LIT:			s = "INT_LIT";		break;
				case STRING_LIT:	s = "STRING_LIT";	break;
				case TRI_STRING_LIT:	s = "TRI_STRING_LIT";	break;
				default: "BAD TOKEN";
			}
			
			printf("%d  %s \"%s\"\n", yylineno, s, yytext);
			//printf("%d  %s \"%s\"\n", line_numb, s, yytext);
	  }

    //if (tok == '\n') line_numb++;
  }
}
