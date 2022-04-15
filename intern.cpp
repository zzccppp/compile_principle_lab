#include "intern.hpp"
#include "ast.h"
#include "semantic.h"
#include <iostream>

void IRGenerator::addStructures(StructDefTable& structs) {
  
}

void IRGenerator::addFunctions(FunctionTable& funcs) {

}


void IRGenerator::genIR(pASTNode node) {
  if (node == nullptr) {
    return;
  }
  if (!strcmp(node->name, "ExtDef")) {
    genExtDef(node);
  }

  for (size_t i = 0; i < node->child_count; i++) {
    genIR(node->child[i]);
  }
}

void IRGenerator::genExtDef(pASTNode extdef) {
  // 没有全局变量,只处理FunDec CompSt;
  /*
        Specifier ExtDecList SEMI
      | Specifier SEMI
      | Specifier FunDec CompSt
      | Specifier FunDec SEMI
  */
  if (extdef->child_count == 3 && !strcmp(extdef->child[2]->name, "CompSt")) {
    genFunDec(extdef->child[1]);
    genCompSt(extdef->child[2]);
  }
}

void IRGenerator::genFunDec(pASTNode fundec) {

}
void IRGenerator::genCompSt(pASTNode compst) {

}
