#include "ast.h"
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#define LOG( message ) logError( __LINE__, message )
#define UNREACHABLE LOG("Should Not Reach Here")

static inline void logError (int line, const std::string& message)
{
  std::cerr << "[" << line << "]" << message << std::endl;
}

enum Kind { Basic, Array, Structure, Error };
enum BasicType { Int, Float };

struct Field;

struct Type {
public:
  Kind k;
  BasicType basic;
  struct {
    std::shared_ptr<Type> t;
    uint32_t size;
    uint32_t dim;
  } array;
  struct {
    std::vector<Field> fields;
    std::string structName;
    bool unname = false;
  } structure;
  bool eq(Type &other);
};

struct Field {
public:
  std::string name;
  Type type;
};

struct Function {
  std::string name;
  std::vector<Field> fields;
  bool has_body;
};

using FunctionTable = std::unordered_map<std::string, Function>;
using FieldTable = std::unordered_map<std::string, Field>;
using StructDefTable = std::unordered_map<std::string, Type>;

class SymTable {
private:
  FunctionTable functionTable;
  std::stack<FieldTable> fieldTableStack;
  StructDefTable structTable;

public:
  SymTable() {
    FieldTable t;
    fieldTableStack.push(t);
  }
  inline void traverseAST(pASTNode node) {
    if (node == nullptr) {
      return;
    }

    if (!strcmp(node->name, "ExtDef")) {
      ExtDef(node);
    }

    for (size_t i = 0; i < node->child_count; i++) {
      traverseAST(node->child[i]);
    }
  }

private:
  void ExtDef(pASTNode node);
  Type Specifier(pASTNode node);
  Type StructSpecifier(pASTNode node);
  void DefList_Struct(pASTNode node, Type *t);
  void Def_Struct(pASTNode node, Type *t);
  void ExtDecList(pASTNode node, Type* t);
};

enum ErrorType {
  UNDEF_VAR = 1,        // Undefined Variable
  UNDEF_FUNC,           // Undefined Function
  REDEF_VAR,            // Redefined Variable
  REDEF_FUNC,           // Redefined Function
  TYPE_MISMATCH_ASSIGN, // Type mismatchedfor assignment.
  LEFT_VAR_ASSIGN,  // The left-hand side of an assignment must be a variable.
  TYPE_MISMATCH_OP, // Type mismatched for operands.
  TYPE_MISMATCH_RETURN, // Type mismatched for return.
  FUNC_AGRC_MISMATCH,   // Function is not applicable for arguments
  NOT_A_ARRAY,          // Variable is not a Array
  NOT_A_FUNC,           // Variable is not a Function
  NOT_A_INT,            // Variable is not a Integer
  ILLEGAL_USE_DOT,      // Illegal use of "."
  NONEXISTFIELD,        // Non-existentfield
  REDEF_FEILD,          // Redefined field
  DUPLICATED_NAME,      // Duplicated name
  UNDEF_STRUCT,         // Undefined structure
  FUNC_ONLY_DEF,
  FUNC_MULTI_DEF,
};

static inline void printSemanticError(ErrorType type, int lineno,
                                      std::string msg) {
  std::cout << "Error type " << type << " at Line " << lineno << ": " << msg
            << std::endl;
}

static inline bool isNameExists(std::vector<Field> &field, std::string name) {
  for (auto var : field) {
    if (var.name == name) {
      return true;
    }
  }
  return false;
}

static inline int getINTValue(pASTNode node) {
  if (node->type != tokINT){
    std::cerr << "Should Has Some Bugs\n";
    return 0;
  }
  size_t len = strlen(node->val);
  int x;
  if (node->val[0] == '0') {
    if (len > 2 && (node->val[1] == 'x' || node->val[1] == 'X')) {
      sscanf(node->val, "%x", &x);
    } else {
      sscanf(node->val, "%o", &x);
    }
  } else {
    sscanf(node->val, "%d", &x);
  }
  return x;
}
