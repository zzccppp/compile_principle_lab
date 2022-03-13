#pragma once

typedef enum {
  tokINT,
  tokFLOAT,
  tokID,
  tokTYPE,
  tokINTERNAL,
} NodeType;

typedef struct astNode {
  int lineNum;
  NodeType type;
  char* name;
  char* val;
  struct astNode* child;
  unsigned int child_count;
} ASTNode;

typedef ASTNode* pASTNode;
