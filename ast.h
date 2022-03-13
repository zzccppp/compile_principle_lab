#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
  tokINT,
  tokFLOAT,
  tokID,
  tokTYPE,
  tokKEYWORD,
  tokOP,
  tokPAIR,
  nodeINTERNAL,
} NodeType;

typedef struct astNode {
  int lineNum;
  int startColumn;
  int endColumn;
  NodeType type;
  char* name;
  char* val;
  struct astNode** child;
  unsigned int child_count;
} ASTNode;

typedef ASTNode* pASTNode;

pASTNode newTokenNode(int lineNum, int startColumn, int endColumn, NodeType type,char* tokName, char* tokText);

pASTNode newInternalNode(int lineNum, char* tokName, int argc, ...);

void printASTTree(pASTNode node, int depth);