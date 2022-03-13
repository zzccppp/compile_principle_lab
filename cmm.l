D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			([Ee][+-]?{D}+)
P           ([Pp][+-]?{D}+)
FS			(f|F|l|L)
IS          ((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))

%option noyywrap nodefault yylineno

%{
#include <stdio.h>
#include "ast.h"
#include "cmm.tab.h"
void comment(void);

int yycolumn = 1;
#define YY_USER_ACTION \
    yylloc.first_line=yylloc.last_line=yylineno; \
    yylloc.first_column=yycolumn; \
    yylloc.last_column=yycolumn+yyleng-1; \
    yycolumn+=yyleng;

%}

%%
"/*"			{ comment(); }
"//"[^\n]*              {  }

0[xX]{H}+{IS}?		{ yylval.node = 0; return INT; }
0[0-7]*{IS}?		{ return INT; }
[1-9]{D}*{IS}?		{ return INT; }

{D}+{E}{FS}?		{ return FLOAT; }
{D}*"."{D}+{E}?{FS}?	{ return FLOAT; }
{D}+"."{D}*{E}?{FS}?	{ return FLOAT; }

"struct" { return STRUCT; }
"return" { return RETURN; }
"if" { return IF; }
"else" { return ELSE; }
"while" { return WHILE; }
("int"|"float") { return TYPE; }

{L}({L}|{D})*		{ return ID; }

L?\"(\\.|[^\\"\n])*\"	{ return STRING_LITERAL; }

";" { return SEMI; }
","	{ return COMMA; }
"=" { return ASSIGNOP; }
("<"|">"|"<="|">="|"=="|"!=") { return ASSIGNOP; }
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return STAR; }
"/" { return DIV; }
"&&" { return AND; }
"||" { return OR; }
"." { return DOT; }
"!" { return NOT; }

"(" { return LP; }
")" { return RP; }
"[" { return LB; }
"]" { return RB; }
"{" { return LC; }
"}" { return RC; }

[ \n\r ] { yycolumn = 1; }
[ \t\v\n\f ] {  }

. { printf("Illegal character: %c\n", yytext[0]); }

%%

void comment(void)
{
	char c, prev = 0;
  
	while ((c = input()) != 0)      /* (EOF maps to 0) */
	{
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
	printf("unterminated comment");
}

