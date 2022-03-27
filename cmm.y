%{
#include <stdio.h>
#include "ast.h"
#include "lex.yy.h"
#define YYERROR_VERBOSE 1
extern int synError;

int yyerror(char*);
void printErrorMsg(char type, int lineno, char* msg);
pASTNode root;
%}

%union {
  pASTNode node;
}

%token <node> ID INT FLOAT STRING_LITERAL
%token <node> SEMI COMMA ASSIGNOP RELOP
%token <node> PLUS MINUS STAR DIV AND OR DOT NOT
%token <node> TYPE LP RP LB RB LC RC
%token <node> STRUCT RETURN IF ELSE WHILE

%type <node> Program ExtDefList ExtDef ExtDecList   //  High-level Definitions
%type <node> Specifier StructSpecifier OptTag Tag   //  Specifiers
%type <node> VarDec FunDec VarList ParamDec         //  Declarators
%type <node> CompSt StmtList Stmt                   //  Statements
%type <node> DefList Def Dec DecList                //  Local Definitions
%type <node> PrimaryExp PostfixExp UnaryExp UnaryOp MultiplicativeExp AdditiveExp RelationalExp AndExp OrExp AssignmentExp //specfic expressions
%type <node> Exp Args                               //  Expressions

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%locations

%%

Program:
       ExtDefList { $$ = newInternalNode(@$.first_line, "Program", 1, $1); root = $$; }
       ;

ExtDefList:
          %empty { $$ = 0; }
          | ExtDef ExtDefList { $$ = newInternalNode(@$.first_line, "ExtDefList", 2, $1, $2); }
          ;

ExtDef: 
      Specifier ExtDecList SEMI { $$ = newInternalNode(@$.first_line, "ExtDef", 3, $1, $2, $3); }
      | Specifier SEMI  { $$ = newInternalNode(@$.first_line, "ExtDef", 2, $1, $2); }
      | Specifier FunDec CompSt  { $$ = newInternalNode(@$.first_line, "ExtDef", 3, $1, $2, $3); }
      | Specifier FunDec SEMI { $$ = newInternalNode(@$.first_line, "ExtDef", 3, $1, $2, $3); }
      | Specifier FunDec error { }
      | Specifier error { synError = 1; printErrorMsg('B', @2.first_line, "missing ; (in Specifier)"); }
      ;

ExtDecList:
          VarDec  { $$ = newInternalNode(@$.first_line, "ExtDecList", 1, $1); }
          | VarDec COMMA ExtDecList  { $$ = newInternalNode(@$.first_line, "ExtDecList", 3, $1, $2, $3); }
          ;

Specifier:
         TYPE  { $$ = newInternalNode(@$.first_line, "Specifier", 1, $1); }
         | StructSpecifier  { $$ = newInternalNode(@$.first_line, "Specifier", 1, $1); }
         ;

StructSpecifier:
               STRUCT OptTag LC DefList RC  { $$ = newInternalNode(@$.first_line, "StructSpecifier", 5, $1, $2, $3, $4, $5); }
               | STRUCT Tag  { $$ = newInternalNode(@$.first_line, "StructSpecifier", 2, $1, $2); }
               ;

OptTag: %empty { $$ = 0; }
      | ID  { $$ = newInternalNode(@$.first_line, "OptTag", 1, $1); }
      ;

Tag: ID  { $$ = newInternalNode(@$.first_line, "Tag", 1, $1); }
   ;

VarDec: ID  { $$ = newInternalNode(@$.first_line, "VarDec", 1, $1); }
      | VarDec LB INT RB  { $$ = newInternalNode(@$.first_line, "VarDec", 4, $1, $2, $3, $4); }
      /* | error RB { synError = 1; printErrorMsg('B', @1.first_line, "[][][][]"); } */
      ;

FunDec: ID LP VarList RP { $$ = newInternalNode(@$.first_line, "FunDec", 4, $1, $2, $3, $4); }
      | ID LP RP { $$ = newInternalNode(@$.first_line, "FunDec", 3, $1, $2, $3); }
      ;

VarList:
       ParamDec COMMA VarList  { $$ = newInternalNode(@$.first_line, "VarList", 3, $1, $2, $3); }
       | ParamDec  { $$ = newInternalNode(@$.first_line, "VarList", 1, $1); }
       ;

ParamDec:
        Specifier VarDec  { $$ = newInternalNode(@$.first_line, "ParamDec", 2, $1, $2); }
        ;

CompSt:
      LC DefList StmtList RC  { $$ = newInternalNode(@$.first_line, "CompSt", 4, $1, $2, $3, $4); }
      ;

StmtList:
        %empty { $$ = 0; }
        | Stmt StmtList  { $$ = newInternalNode(@$.first_line, "StmtList", 2, $1, $2); }
        ;

Stmt: Exp SEMI  { $$ = newInternalNode(@$.first_line, "Stmt", 2, $1, $2); }
    | CompSt  { $$ = newInternalNode(@$.first_line, "Stmt", 1, $1); }
    | RETURN Exp SEMI  { $$ = newInternalNode(@$.first_line, "Stmt", 3, $1, $2, $3); }
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE  { $$ = newInternalNode(@$.first_line, "Stmt", 5, $1, $2, $3, $4, $5); }
    | IF LP Exp RP Stmt ELSE Stmt  { $$ = newInternalNode(@$.first_line, "Stmt", 6, $1, $2, $3, $4, $5, $6); }
    | WHILE LP Exp RP Stmt  { $$ = newInternalNode(@$.first_line, "Stmt", 5, $1, $2, $3, $4, $5); }
    | Exp error { synError = 1; printErrorMsg('B', @2.first_line, "missing ; (in Exp)"); }
    ;


DefList:
       %empty { $$ = 0; }
       | Def DefList  { $$ = newInternalNode(@$.first_line, "DefList", 2, $1, $2); }
       ;

Def: Specifier DecList SEMI  { $$ = newInternalNode(@$.first_line, "Def", 3, $1, $2, $3); }
    | Specifier DecList error { synError = 1; printErrorMsg('B', @3.first_line, "missing ; (in Def)"); }
   ;

DecList: Dec  { $$ = newInternalNode(@$.first_line, "DecList", 1, $1); }
       | Dec COMMA DecList  { $$ = newInternalNode(@$.first_line, "DecList", 3, $1, $2, $3); }
       ;

Dec: VarDec  { $$ = newInternalNode(@$.first_line, "Dec", 1, $1); }
   | VarDec ASSIGNOP AssignmentExp  { $$ = newInternalNode(@$.first_line, "Dec", 3, $1, $2, $3); }
   ;

/* Exp: */
/*    Exp ASSIGNOP Exp */
/*    | Exp AND Exp */
/*    | Exp OR Exp */
/*    | Exp RELOP Exp */
/*    | Exp PLUS Exp */
/*    | Exp MINUS Exp */
/*    | Exp STAR Exp */
/*    | Exp DIV Exp */
/*    | LP Exp RP */
/*    | MINUS Exp */
/*    | NOT Exp */
/*    | ID LP Args RP */
/*    | ID LP RP */
/*    | Exp LB Exp RB */
/*    | Exp DOT ID */
/*    | ID */
/*    | INT */
/*    | FLOAT */
/*    ; */

PrimaryExp:
          ID   { $$ = newInternalNode(@$.first_line, "Exp", 1, $1); }
          | INT  { $$ = newInternalNode(@$.first_line, "Exp", 1, $1); }
          | FLOAT  { $$ = newInternalNode(@$.first_line, "Exp", 1, $1); }
          | STRING_LITERAL  { $$ = newInternalNode(@$.first_line, "Exp", 1, $1); }
          | LP Exp RP   { $$ = newInternalNode(@$.first_line, "Exp", 3, $1); }
          ;

PostfixExp:
          /* PrimaryExp  { $$ = newInternalNode(@$.first_line, "PostfixExp", 1, $1); } */
          PrimaryExp  { $$ = $1; }
          | PostfixExp LB AssignmentExp RB  { $$ = newInternalNode(@$.first_line, "Exp", 4, $1, $2, $3, $4); }
          | PostfixExp LP RP  { $$ = newInternalNode(@$.first_line, "Exp", 3, $1, $2, $3); }
          | PostfixExp DOT ID   { $$ = newInternalNode(@$.first_line, "Exp", 3, $1, $2, $3); }
          | PostfixExp LP Args RP  { $$ = newInternalNode(@$.first_line, "Exp", 4, $1, $2, $3, $4); }
          | PostfixExp LB error RB { synError = 1; printErrorMsg('B', @3.first_line, "error in []");}
          ; 

UnaryExp:
        /* PostfixExp  { $$ = newInternalNode(@$.first_line, "UnaryExp", 1, $1); } */
        PostfixExp  { $$ = $1; }
        | UnaryOp UnaryExp  { $$ = newInternalNode(@$.first_line, "Exp", 2, $1, $2); }
        ;

UnaryOp:
       /* MINUS  { $$ = newInternalNode(@$.first_line, "UnaryOp", 1, $1); } */
       MINUS  { $$ = $1; }
       /* | NOT  { $$ = newInternalNode(@$.first_line, "UnaryOp", 1, $1); } */
       | NOT  { $$ = $1; }
       ;

MultiplicativeExp:
                 /* UnaryExp  { $$ = newInternalNode(@$.first_line, "MultiplicativeExp", 1, $1); } */
                 UnaryExp  { $$ = $1; }
                 | MultiplicativeExp STAR UnaryExp  { $$ = newInternalNode(@$.first_line, "Exp", 3, $1, $2, $3); }
                 | MultiplicativeExp DIV UnaryExp  { $$ = newInternalNode(@$.first_line, "Exp", 3, $1, $2, $3); }
                 ;

AdditiveExp:
           /* MultiplicativeExp  { $$ = newInternalNode(@$.first_line, "AdditiveExp", 1, $1); } */
           MultiplicativeExp  { $$ = $1; }
           | AdditiveExp PLUS MultiplicativeExp  { $$ = newInternalNode(@$.first_line, "Exp", 3, $1, $2, $3); }
           | AdditiveExp MINUS MultiplicativeExp  { $$ = newInternalNode(@$.first_line, "Exp", 3, $1, $2, $3); }
           ;

RelationalExp:
             /* AdditiveExp  { $$ = newInternalNode(@$.first_line, "RelationalExp", 1, $1); } */
             AdditiveExp  { $$ = $1; }
             | RelationalExp RELOP AdditiveExp  { $$ = newInternalNode(@$.first_line, "Exp", 3, $1, $2, $3); }
             ;

AndExp:
      /* RelationalExp  { $$ = newInternalNode(@$.first_line, "AndExp", 1, $1); } */
      RelationalExp  { $$ = $1; }
      | AndExp AND RelationalExp  { $$ = newInternalNode(@$.first_line, "Exp", 3, $1, $2, $3); }
      ;

OrExp:
     /* AndExp  { $$ = newInternalNode(@$.first_line, "OrExp", 1, $1); } */
     AndExp  { $$ = $1; }
     | OrExp OR AndExp  { $$ = newInternalNode(@$.first_line, "Exp", 3, $1, $2, $3); }
     ;


AssignmentExp:
             /* OrExp  { $$ = newInternalNode(@$.first_line, "AssignmentExp", 1, $1); } */
             OrExp  { $$ = $1; }
             | PostfixExp ASSIGNOP AssignmentExp  { $$ = newInternalNode(@$.first_line, "Exp", 3, $1, $2, $3); }
             ;

Exp:
   AssignmentExp  { $$ = $1; }
   | Exp COMMA AssignmentExp  { $$ = newInternalNode(@$.first_line, "Exp", 3, $1, $2, $3); }
   ;

Args:
    AssignmentExp  { $$ = newInternalNode(@$.first_line, "Args", 1, $1); }
    | Args COMMA AssignmentExp  { $$ = newInternalNode(@$.first_line, "Args", 3, $1, $2, $3); }
    ;

%%

int yyerror(char *s) {
  synError = 1;
  fprintf(stderr, "Error type B at line %d: %s.\n", yylineno, s);
  return 0;
}

void printErrorMsg(char type, int lineno, char* msg) {
  fprintf(stderr, "Error type %c at line %d: %s.\n", type,lineno,msg);
}
