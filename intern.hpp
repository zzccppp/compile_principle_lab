#pragma once

#include "ast.h"
#include "semantic.h"
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

enum OpKind {
  OP_VARIABLE,
  OP_CONSTANT,
  OP_ADDRESS,
  OP_LABEL,
  OP_FUNCTION,
  OP_RELOP,
};

struct Operand {
  OpKind kind;
  int value;
  std::string name;
};

enum IRKind {
  IR_LABEL,
  IR_FUNCTION,
  IR_ASSIGN,
  IR_ADD,
  IR_SUB,
  IR_MUL,
  IR_DIV,
  IR_GET_ADDR,
  IR_READ_ADDR,
  IR_WRITE_ADDR,
  IR_GOTO,
  IR_IF_GOTO,
  IR_RETURN,
  IR_DEC,
  IR_ARG,
  IR_CALL,
  IR_PARAM,
  IR_READ,
  IR_WRITE,
};

struct InterCode {
  IRKind kind;
  struct {
    Operand op;
  } oneOp;
  struct {
    Operand right, left;
  } assign;
  struct {
    Operand result, op1, op2;
  } binOp;
  struct {
    Operand x, relop, y, z;
  } ifGoto;
  struct {
    Operand op;
    int size;
  } dec;
};

struct InterCodeList {
  int tempVarNumber;
  int labelNumber;
  std::vector<InterCode> codes;
};

class IRGenerator {
private:
public:
  void addStructures(StructDefTable &structs);
  void addFunctions(FunctionTable &funcs);
  void genIR(pASTNode root);
  void genExtDef(pASTNode root);
  void genFunDec(pASTNode fundec);
  void genCompSt(pASTNode compst);
};
