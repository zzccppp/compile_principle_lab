#pragma once

#include "ast.h"
#include "semantic.h"
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

enum OpKind {
    OP_VARIABLE,
    OP_CONSTANT,
    OP_ADDRESS,
    OP_LABEL,
    OP_FUNCTION,
    OP_RELOP,
    OP_SIZE,
};

struct Operand {
    OpKind kind;
    int value;
    std::string name;

    Operand() = default;

    Operand(OpKind kind, int value) {
        this->kind = kind;
        this->value = value;
    }

    Operand(OpKind kind, const std::string &s) {
        this->kind = kind;
        this->name = s;
    }

    friend std::ostream &operator<<(std::ostream &os, const Operand &operand);
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

    friend std::ostream &operator<<(std::ostream &os, const InterCode &code);

    /**
     * 对于 IR_DEC 需要传入的是op1 value
     * @param kind
     * @param ops
     */
    void genInterCode(IRKind kind, std::initializer_list<Operand> ops) {
        this->kind = kind;
        switch (kind) {
            case IR_LABEL:
            case IR_FUNCTION:
            case IR_GOTO:
            case IR_RETURN:
            case IR_ARG:
            case IR_PARAM:
            case IR_READ:
            case IR_WRITE:
                assert(ops.size() == 1);
                this->oneOp.op = *ops.begin();
                break;
            case IR_ASSIGN:
            case IR_GET_ADDR:
            case IR_READ_ADDR:
            case IR_WRITE_ADDR:
            case IR_CALL:
                assert(ops.size() == 2);
                this->assign.left = *ops.begin();
                this->assign.right = *(ops.begin() + 1);
                break;
            case IR_ADD:
            case IR_SUB:
            case IR_MUL:
            case IR_DIV:
                assert(ops.size() == 3);
                this->binOp.result = *ops.begin();
                this->binOp.op1 = *(ops.begin() + 1);
                this->binOp.op2 = *(ops.begin() + 2);
                break;
            case IR_DEC:
                assert(ops.size() == 2);
                this->dec.op = *(ops.begin());
                this->dec.size = (ops.begin() + 1)->value;
                break;
            case IR_IF_GOTO:
                assert(ops.size() == 4);
                this->ifGoto.x = *ops.begin();
                this->ifGoto.relop = *(ops.begin() + 1);
                this->ifGoto.y = *(ops.begin() + 2);
                this->ifGoto.z = *(ops.begin() + 3);
        }
    }
};

struct InterCodeList {
    int tempVarNumber;
    int labelNumber;
    std::vector<InterCode> codes;

    InterCodeList() {
        tempVarNumber = 1;
        labelNumber = 1;
    }

    Operand newTemp();

    Operand newLabel();

    void genIRCode(IRKind kind, std::initializer_list<Operand> ops);

    void printIRCodes() {
        for (const auto &item: codes) {
            std::cout << item << std::endl;
        }
    }
};

class IRGenerator {
private:
    InterCodeList codes;
    StructDefTable structs;
    FunctionTable funcs;
    FieldTable sym;
public:
    void addStructures(StructDefTable &structs);

    void addFunctions(FunctionTable &funcs);

    void addSymbols(FieldTable &tab) {
        sym = tab;
    }

    Type expType(pASTNode exp);

    void genIR(pASTNode root);

    void genExtDef(pASTNode root);

    void genFunDec(pASTNode funDec);

    void genCompSt(pASTNode compSt);

    void genDefList(pASTNode defList);

    void genStmtList(pASTNode stmtList);

    void genDef(pASTNode def);

    void genDec(pASTNode dec);

    void genVarDec(pASTNode vardec, Operand* place);

    void genExp(pASTNode exp, Operand* place);

    void genCond(pASTNode exp, Operand* label1, Operand* label2);

    void genStmt(pASTNode stmt);

    inline void printIRCodes() {
        codes.printIRCodes();
    }
};
