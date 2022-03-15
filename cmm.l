D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			([Ee][+-]?{D}+)
P           ([Pp][+-]?{D}+)
FS			(f|F|l|L)
IS          ((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))
ID {L}({L}|{D})*

%option noyywrap nodefault yylineno

%{
#include <stdio.h>
#include "ast.h"
#include "cmm.tab.h"
void comment(void);

extern unsigned int lexError;

int yycolumn = 1;
#define YY_USER_ACTION \
    yylloc.first_line=yylloc.last_line=yylineno; \
    yylloc.first_column=yycolumn; \
    yylloc.last_column=yycolumn+yyleng-1; \
    yycolumn+=yyleng;

%}

%%
\n|\r { yycolumn = 1; }
"/*"			{ comment(); }
"//"[^\n]*              {  }

0[xX]{H}+{IS}?		{ yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column , tokINT, "INT", yytext); return INT; }
0[0-7]*{IS}?		{ yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column , tokINT, "INT", yytext); return INT; }
[1-9]{D}*{IS}?		{ yylval.node = newTokenNode(yylineno, yylloc.first_column , yylloc.last_column , tokINT, "INT", yytext); return INT; }

{D}+{E}{FS}?		{ yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokFLOAT, "FLOAT", yytext); return FLOAT; }
{D}*"."{D}+{E}?{FS}?	{ yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokFLOAT, "FLOAT", yytext); return FLOAT; }
{D}+"."{D}*{E}?{FS}?	{ yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokFLOAT, "FLOAT", yytext); return FLOAT; }

"struct" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokKEYWORD, "STRUCT", yytext); return STRUCT; }
"return" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokKEYWORD, "RETURN", yytext); return RETURN; }
"if" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokKEYWORD, "IF", yytext); return IF; }
"else" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokKEYWORD, "ELSE", yytext); return ELSE; }
"while" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokKEYWORD, "WHILE", yytext); return WHILE; }

("int"|"float") { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokTYPE, "TYPE", yytext); return TYPE; }

{L}({L}|{D})*		{ yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokID, "ID", yytext); return ID; }

L?\"(\\.|[^\\"\n])*\"	{ return STRING_LITERAL; }

";" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokOP, "SEMI", yytext); return SEMI; }
","	{ yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokOP, "COMMA", yytext); return COMMA; }
"=" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokOP, "ASSIGNOP", yytext); return ASSIGNOP; }
("<"|">"|"<="|">="|"=="|"!=") { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokOP, "RELOP", yytext); return RELOP; }
"+" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokOP, "PLUS", yytext); return PLUS; }
"-" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokOP, "MINUS", yytext); return MINUS; }
"*" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokOP, "STAR", yytext); return STAR; }
"/" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokOP, "DIV", yytext); return DIV; }
"&&" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokOP, "AND", yytext); return AND; }
"||" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokOP, "OR", yytext); return OR; }
"." { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokOP, "DOT", yytext); return DOT; }
"!" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokOP, "NOT", yytext); return NOT; }

"(" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokPAIR, "LP", yytext); return LP; }
")" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokPAIR, "RP", yytext); return RP; }
"[" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokPAIR, "LB", yytext); return LB; }
"]" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokPAIR, "RB", yytext); return RB; }
"{" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokPAIR, "LC", yytext); return LC; }
"}" { yylval.node = newTokenNode(yylineno, yylloc.first_column, yylloc.last_column, tokPAIR, "RC", yytext); return RC; }

[ \t\v\n\f ] {  }

0[xX][0-9a-zA-Z]*  {lexError = 1; printf("Error type A at Line %d: Illegal Hex Number \"%s\".\n", yylineno, yytext); }
0[0-9]+  {lexError = 1; printf("Error type A at Line %d: Illegal Octal Number \"%s\".\n", yylineno, yytext); }
{D}+{ID} {lexError = 1; printf("Error type A at Line %d: Illegal ID \"%s\".\n", yylineno, yytext); }
"."{D}+ { lexError = 1; printf("Error type A at Line %d: Illegal floating point number \"%s\".\n", yylineno, yytext); }
{D}+"." { lexError = 1; printf("Error type A at Line %d: Illegal floating point number \"%s\".\n", yylineno, yytext); }
{D}*"."{D}+[eE] { lexError = 1; printf("Error type A at Line %d: Illegal floating point number \"%s\".\n", yylineno, yytext); }
{D}+"."{D}*[eE] { lexError = 1; printf("Error type A at Line %d: Illegal floating point number \"%s\".\n", yylineno, yytext); }
{D}+[eE][+-]?{D}* { lexError = 1; printf("Error type A at Line %d: Illegal floating point number \"%s\".\n", yylineno, yytext); }
"."[eE][+-]?{D}+ { lexError = 1; printf("Error type A at Line %d: Illegal floating point number \"%s\".\n", yylineno, yytext); }
. { lexError = 1; printf("Error type A at Line %d: Mysterious character \'%s\'.\n", yylineno, yytext); }

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

