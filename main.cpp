extern "C" {
#include "ast.h"
#include "cmm.tab.h"
#include "lex.yy.h"
}
#include "semantic.h"
#include <iostream>

extern pASTNode root;

unsigned int lexError = 0;
unsigned int synError = 0;

int main(int argc, char **argv) {
  if (argc <= 1) {
    yyparse();
    return 0;
  }

  FILE *f = fopen(argv[1], "r");

  if (!f) {
    perror(argv[1]);
    return 1;
  }

  yyrestart(f);
  yyparse();
  if (!lexError && !synError) {
    printASTTree(root, 0);
    SymTable t;
    t.traverseAST(root);
    t.checkFunction();
  }
  return 0;
}
