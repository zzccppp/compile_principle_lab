#include "ast.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

pASTNode newTokenNode(int lineNum, int startColumn, int endColumn,
                      NodeType type, char *tokName, char *tokText) {
  /* printf("%s lineNum: %d,column: (%d,%d)\n", tokName, lineNum, startColumn,
   */
  /*        endColumn); */
  pASTNode node = (pASTNode)malloc(sizeof(ASTNode));

  node->lineNum = lineNum;
  node->startColumn = startColumn;
  node->endColumn = endColumn;
  node->type = type;

  int tokname_len = strlen(tokName);
  int toktext_len = strlen(tokText);

  node->name = malloc(sizeof(char) * (tokname_len + 1));
  node->val = malloc(sizeof(char) * (toktext_len + 1));
  strcpy(node->name, tokName);
  strcpy(node->val, tokText);

  node->child = 0;
  node->child_count = 0;

  return node;
}

pASTNode newInternalNode(int lineNum, char *tokName, int argc, ...) {
  /* printf("%s lineNum: %d\n", tokName, lineNum); */
  pASTNode node = (pASTNode)malloc(sizeof(ASTNode));
  node->lineNum = lineNum;
  node->startColumn = 0;
  node->endColumn = 0;
  node->type = nodeINTERNAL;

  int tokname_len = strlen(tokName);
  node->name = malloc(sizeof(char) * (tokname_len + 1));
  strcpy(node->name, tokName);

  node->child_count = argc;

  node->child = malloc(sizeof(pASTNode) * argc);

  va_list argptr;
  va_start(argptr, argc);
  for (size_t i = 0; i < argc; i++) {
    node->child[i] = va_arg(argptr, pASTNode);
  }

  return node;
}

int isTokenNode(pASTNode n) {
  NodeType t = n->type;
  return t == tokINT || t == tokOP || t == tokTYPE || t == tokFLOAT ||
         t == tokID || t == tokKEYWORD || t == tokPAIR;
}

void printASTTree(pASTNode node, int depth) {
  if (node == 0) {
    return;
  }
  for (int i = 0; i < depth; i++) {
    printf("  ");
  }
  if (node->type == tokID) {
    printf("%s: %s\n", node->name, node->val);
  } else if (node->type == tokTYPE) {
    printf("%s: %s\n", node->name, node->val);
  } else if (node->type == tokINT) {
    printf("%s: %s\n", node->name, node->val);
  } else if (node->type == tokFLOAT) {
    printf("%s: %s\n", node->name, node->val);
  } else if (isTokenNode(node)) {
    printf("%s\n", node->name);
  } else {
    printf("%s (%d)\n", node->name, node->lineNum);
  }
  for (size_t i = 0; i < node->child_count; i++) {
    printASTTree(node->child[i], depth + 1);
  }
}
