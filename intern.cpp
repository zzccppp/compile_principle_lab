#include "intern.hpp"
#include "ast.h"
#include "semantic.h"
#include <iostream>
#include <sstream>

std::ostream &operator<<(std::ostream &os, const Operand &operand) {

    return os;
}

void IRGenerator::addStructures(StructDefTable &structs) {
    this->structs = structs;
}

void IRGenerator::addFunctions(FunctionTable &funcs) {
    this->funcs = funcs;
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

void IRGenerator::genFunDec(pASTNode funDec) {

}

void IRGenerator::genCompSt(pASTNode compSt) {

}

Operand InterCodeList::newTemp() {
    Operand op;
    op.kind = OpKind::OP_VARIABLE;
    std::stringstream ss;
    ss << "t" << labelNumber;
    op.name = ss.str();
    labelNumber += 1;
    return op;
}

void InterCodeList::genIRCode(IRKind kind, std::initializer_list<Operand> ops) {
    Operand temp;
    Operand result, op1, op2, relop;
    int size = 0;
    InterCode newCode;

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
            op1 = *ops.begin();
            if (op1.kind == OP_ADDRESS) {
                temp = newTemp();
                genIRCode(IR_READ_ADDR, {temp, op1});
                op1 = temp;
            }
            newCode.genInterCode(kind, {op1});
            codes.push_back(newCode);
            break;
        case IR_ASSIGN:
        case IR_GET_ADDR:
        case IR_READ_ADDR:
        case IR_WRITE_ADDR:
        case IR_CALL:
            op1 = *ops.begin();
            op2 = *(ops.begin() + 1);
            if (kind == IR_ASSIGN &&
                (op1.kind == OP_ADDRESS || op2.kind == OP_ADDRESS)) {
                if (op1.kind == OP_ADDRESS && op2.kind != OP_ADDRESS)
                    genIRCode(IR_WRITE_ADDR, {op1, op2});
                else if (op2.kind == OP_ADDRESS && op1.kind != OP_ADDRESS)
                    genIRCode(IR_READ_ADDR, {op1, op2});
                else {
                    temp = newTemp();
                    genIRCode(IR_READ_ADDR, {temp, op2});
                    genIRCode(IR_WRITE_ADDR, {op1, temp});
                }
            } else {
                newCode.genInterCode(kind, {op1, op2});
                codes.push_back(newCode);
            }
            break;
        case IR_ADD:
        case IR_SUB:
        case IR_MUL:
        case IR_DIV:
            result = *ops.begin();
            op1 = *(ops.begin() + 1);
            op2 = *(ops.begin() + 2);
            if (op1.kind == OP_ADDRESS) {
                temp = newTemp();
                genIRCode(IR_READ_ADDR, {temp, op1});
                op1 = temp;
            }
            if (op2.kind == OP_ADDRESS) {
                temp = newTemp();
                genIRCode(IR_READ_ADDR, {temp, op2});
                op2 = temp;
            }
            newCode.genInterCode(kind, {result, op1, op2});
            codes.push_back(newCode);
            break;

        case IR_DEC:
            newCode.genInterCode(kind, ops);
            codes.push_back(newCode);
            break;

        case IR_IF_GOTO:
            newCode.genInterCode(kind, ops);
            codes.push_back(newCode);
            break;
    }
}

