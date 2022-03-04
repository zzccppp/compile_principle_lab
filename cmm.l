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
#include "cmm.tab.h"
void comment(void);
// #include "y.tab.h"
/*
enum TokenType {
	INT = 258,
	FLOAT,
	ID,
	SEMI,
	COMMA,
	ASSIGNOP,
	RELOP,
	PLUS,
	MINUS,
	STAR,
	DIV,
	AND,
	OR,
	DOT,
	NOT,
	TYPE,
	LP,
	RP,
	LB,
	RB,
	LC,
	RC,
	STRUCT,
	RETURN,
	IF,
	ELSE,
	WHILE,

	STRING_LITERAL,

};
*/
%}

%%
"/*"			{ comment(); }
"//"[^\n]*              {  }

0[xX]{H}+{IS}?		{ printf("NUMBER\n"); return INT; }
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


[ \t\v\n\f] {  }

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

