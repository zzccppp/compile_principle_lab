%{
#include <stdio.h>
%}

%token ID INT FLOAT STRING_LITERAL
%token SEMI COMMA ASSIGNOP RELOP
%token PLUS MINUS STAR DIV AND OR DOT NOT
%token TYPE LP RP LB RB LC RC
%token STRUCT RETURN IF ELSE WHILE



%%

Program:
       ExtDefList
       ;

ExtDefList:
          %empty
          | ExtDef ExtDefList
          ;

ExtDef: 
      Specifier ExtDecList SEMI
      | Specifier SEMI
      | Specifier FunDec CompSt
      ;

ExtDecList:
          VarDec
          | VarDec COMMA ExtDecList
          ;

Specifier:
         TYPE
         | StructSpecifier
         ;

StructSpecifier:
               STRUCT OptTag LC DefList RC
               | STRUCT Tag
               ;

OptTag: %empty
      | ID
      ;

Tag: ID;

VarDec: ID
      | VarDec LB INT RB
      ;

FunDec: ID LP VarList RP
      | ID LP RP 
      ;

VarList:
       ParamDec COMMA VarList
       | ParamDec
       ;

ParamDec:
        Specifier VarDec
        ;

CompSt:
      LC DefList StmtList RC
      ;

StmtList:
        %empty
        | Stmt StmtList;

Stmt: Exp SEMI
    | CompSt
    | RETURN Exp SEMI
    | IF LP Exp RP Stmt
    | IF LP Exp RP Stmt ELSE Stmt
    | WHILE LP Exp RP Stmt
    ;


DefList:
       %empty
       | Def DefList
       ;

Def: Specifier DecList SEMI
   ;

DecList: Dec
       | Dec COMMA DecList
       ;

Dec: VarDec
   | VarDec ASSIGNOP Exp
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
          ID 
          | INT
          | FLOAT
          | STRING_LITERAL
          | LP Exp RP 
          ;

PostfixExp:
          PrimaryExp
          | PostfixExp LB Exp RB
          | PostfixExp LP RP
          | PostfixExp DOT ID 
          | PostfixExp LP Args RP
          ; 

UnaryExp:
        PostfixExp
        | UnaryOp UnaryExp
        ;

UnaryOp:
       MINUS
       | NOT
       ;

MultiplicativeExp:
                 UnaryExp
                 | MultiplicativeExp STAR UnaryExp
                 | MultiplicativeExp DIV UnaryExp
                 ;

AdditiveExp:
           MultiplicativeExp
           | AdditiveExp PLUS MultiplicativeExp
           | AdditiveExp MINUS MultiplicativeExp
           ;

RelationalExp:
             AdditiveExp
             | RelationalExp RELOP AdditiveExp
             ;

AndExp:
      RelationalExp
      | AndExp AND RelationalExp
      ;

OrExp:
     AndExp
     | OrExp OR AndExp
     ;


AssignmentExp:
             OrExp
             | PostfixExp ASSIGNOP AssignmentExp
             ;

Exp:
   AssignmentExp
   | Exp COMMA AssignmentExp
   ;

Args:
    AssignmentExp
    | Args COMMA AssignmentExp
    ;

%%
