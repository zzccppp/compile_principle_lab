#pragma once

#include "ast.h"
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#define LOG(message) logError(__LINE__, message)
#define UNREACHABLE LOG("Should Not Reach Here")

extern unsigned int semError;

static inline void logError(int line, const std::string &message) {
    std::cerr << "[" << line << "]" << message << std::endl;
}

enum Kind {
    Basic, Array, Structure, Error
};

enum BasicType {
    Int, Float
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
    FUNC_ARG_MISMATCH,    // Function is not applicable for arguments
    NOT_A_ARRAY,          // Variable is not a Array
    NOT_A_FUNC,           // Variable is not a Function
    NOT_A_INT,            // Variable is not a Integer
    ILLEGAL_USE_DOT,      // Illegal use of "."
    NON_EXIST_FIELD,      // Non-existentfield
    REDEF_FEILD,          // Redefined field
    DUPLICATED_NAME,      // Duplicated name
    UNDEF_STRUCT,         // Undefined structure
    FUNC_ONLY_DEF,
    FUNC_MULTI_DEF,
};

static inline void printSemanticError(ErrorType type, int lineno,
                                      std::string msg) {
    semError = 1;
    std::cout << "Error type " << type << " at Line " << lineno << ": " << msg
              << std::endl;
}

struct Field;
struct _FunDecInf;

struct Type {
public:
    Kind k;
    BasicType basic;
    struct {
        std::shared_ptr<Type> t;
        uint32_t size{0};
        uint32_t dim{0};
        std::vector<int> dims;
    } array;
    struct {
        std::vector<Field> fields;
        std::string structName;
        bool unname = false;
    } structure;

    bool eq(Type &other);

    unsigned int size() const;
};

struct Field {
public:
    std::string name;
    Type type;
};

struct Function {
    std::string name;
    Type ret_type;
    std::vector<Field> fields;
    bool has_body;
    int lineno;

    inline bool eq(Function &other) {
        if (name == other.name) {
            if (ret_type.eq(other.ret_type)) {
                if (fields.size() == other.fields.size()) {
                    for (size_t i = 0; i < fields.size(); i++) {
                        if (!fields[i].type.eq(other.fields[i].type)) {
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
        return false;
    }
};

using FunctionTable = std::unordered_map<std::string, Function>;
using FieldTable = std::unordered_map<std::string, Field>;
using StructDefTable = std::unordered_map<std::string, Type>;

class SymTable {
public:
    FunctionTable functionTable;
    std::vector<FieldTable> fieldTableStack;
    StructDefTable structTable;

    FieldTable allFieldTable;

public:
    SymTable() {
        FieldTable t;
        fieldTableStack.push_back(t);

        Type intType;
        intType.k = Kind::Basic;
        intType.basic = BasicType::Int;

        Function w;
        Field w_f;
        w_f.name = "op";
        w_f.type = intType;
        w.fields.push_back(w_f);
        w.has_body = true;
        w.lineno = 0;
        w.name = "write";
        w.ret_type = intType;

        Function r;
        r.has_body = true;
        r.lineno = 0;
        r.name = "read";
        r.ret_type = intType;

        functionTable.insert({"write", w});
        functionTable.insert({"read", r});
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

    inline void checkFunction() {
        // check if the function has body
        for (auto iter = functionTable.begin(); iter != functionTable.end();
             iter++) {
            if (!iter->second.has_body) {
                std::string msg;
                msg.append("The Function ");
                msg.append(iter->second.name);
                msg.append(" has no body");
                printSemanticError(FUNC_ONLY_DEF, iter->second.lineno, msg);
            }
        }
    }

    inline void newFieldTable() {
        FieldTable t;
        fieldTableStack.push_back(t);
    }

    inline void popFieldTable() {
        for (const auto &item: fieldTableStack.back()) {
            allFieldTable.insert(item);
        }
        fieldTableStack.pop_back();
    }

    inline bool isVarNameExists(std::string name) {
        auto fd = this->fieldTableStack.back().find(name);
        if (fd != this->fieldTableStack.back().end()) {
            return true;
        }
        // variable cannot be same name as defined structure
        auto fd1 = this->structTable.find(name);
        if (fd1 != this->structTable.end()) {
            return true;
        }
        return false;
    }

    inline Type findVar(std::string name) {
        // 从栈顶向下搜索
        for (int i = fieldTableStack.size() - 1; i >= 0; i--) {
            auto fd = fieldTableStack[i].find(name);
            if (fd != fieldTableStack[i].end()) {
                return fd->second.type;
            }
        }
        Type t;
        t.k = Kind::Error;
        return t;
    }

private:
    void ExtDef(pASTNode node);

    Type Specifier(pASTNode node);

    Type StructSpecifier(pASTNode node);

    void DefList_Struct(pASTNode node, Type *t);

    void Def_Struct(pASTNode node, Type *t);

    void ExtDecList(pASTNode node, Type *t);

    _FunDecInf FunDec(pASTNode node);

    void CompSt(pASTNode node, const Function &func);

    void DefList_CompSt(pASTNode node, const Function &func);

    void Def_CompSt(pASTNode node, const Function &func);

    Type Exp(pASTNode node);

    void StmtList(pASTNode, const Function &func);

    void Stmt(pASTNode, const Function &func);
};

static inline bool isNameExists(const std::vector<Field> &field,
                                std::string name) {
    for (auto var: field) {
        if (var.name == name) {
            return true;
        }
    }
    return false;
}

static inline int getINTValue(pASTNode node) {
    if (node->type != tokINT) {
        UNREACHABLE;
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

struct _FunDecInf {
    std::string name;
    std::vector<Field> fields;
    bool has_error = false;
};
