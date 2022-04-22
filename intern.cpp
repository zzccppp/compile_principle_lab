#include "intern.hpp"
#include "ast.h"
#include "semantic.h"
#include <iostream>
#include <sstream>

std::ostream &operator<<(std::ostream &os, const Operand &operand) {
  switch (operand.kind) {
  case OP_CONSTANT:
    os << "#" << operand.value;
    break;
  case OP_ADDRESS:
    //            os << "&" << operand.name;
    //            break;
  case OP_VARIABLE:
  case OP_LABEL:
  case OP_FUNCTION:
  case OP_RELOP:
  case OP_SIZE:
    os << operand.name;
    break;
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, const InterCode &code) {
  switch (code.kind) {
  case IR_LABEL:
    os << "LABEL " << code.oneOp.op << " :";
    break;
  case IR_FUNCTION:
    os << "FUNCTION " << code.oneOp.op << " :";
    break;
  case IR_ASSIGN:
    os << code.assign.left << " := " << code.assign.right;
    break;
  case IR_ADD:
    os << code.binOp.result << " := " << code.binOp.op1 << " + "
       << code.binOp.op2;
    break;
  case IR_SUB:
    os << code.binOp.result << " := " << code.binOp.op1 << " - "
       << code.binOp.op2;
    break;
  case IR_MUL:
    os << code.binOp.result << " := " << code.binOp.op1 << " * "
       << code.binOp.op2;
    break;
  case IR_DIV:
    os << code.binOp.result << " := " << code.binOp.op1 << " / "
       << code.binOp.op2;
    break;
  case IR_GET_ADDR:
    os << code.assign.left << " := &" << code.assign.right;
    break;
  case IR_READ_ADDR:
    os << code.assign.left << " := *" << code.assign.right;
    break;
  case IR_WRITE_ADDR:
    os << "*" << code.assign.left << " := " << code.assign.right;
    break;
  case IR_GOTO:
    os << "GOTO " << code.oneOp.op;
    break;
  case IR_IF_GOTO:
    os << "IF " << code.ifGoto.x << " " << code.ifGoto.relop << " "
       << code.ifGoto.y << " GOTO " << code.ifGoto.z;
    break;
  case IR_RETURN:
    os << "RETURN " << code.oneOp.op;
    break;
  case IR_DEC:
    os << "DEC " << code.dec.op << " " << code.dec.size;
    break;
  case IR_ARG:
    os << "ARG " << code.oneOp.op;
    break;
  case IR_CALL:
    os << code.assign.left << " := CALL " << code.assign.right;
    break;
  case IR_PARAM:
    os << "PARAM " << code.oneOp.op;
    break;
  case IR_READ:
    os << "READ " << code.oneOp.op;
    break;
  case IR_WRITE:
    os << "WRITE " << code.oneOp.op;
    break;
  }
  return os;
}

void IRGenerator::addStructures(StructDefTable &structs) {
  this->structs = structs;
}

void IRGenerator::addFunctions(FunctionTable &funcs) { this->funcs = funcs; }

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
  /* FunDec: ID LP VarList RP
      | ID LP RP
      */
  codes.genIRCode(IR_FUNCTION, {Operand(OP_FUNCTION, funDec->child[0]->val)});

  auto fd = this->funcs.find(funDec->child[0]->val);
  auto fields = fd->second.fields;
  for (const auto &item : fields) {
    codes.genIRCode(IR_PARAM, {Operand(OP_VARIABLE, item.name)});
  }
}

void IRGenerator::genCompSt(pASTNode compSt) {
  // LC DefList StmtList RC
  genDefList(compSt->child[1]);
  genStmtList(compSt->child[2]);
}

void IRGenerator::genDefList(pASTNode deflist) {
  /*
 DefList:
   %empty
   | Def DefList
  */
  auto t = deflist;
  while (t != nullptr) {
    genDef(t->child[0]);
    t = t->child[1];
  }
}

void IRGenerator::genStmtList(pASTNode stmtList) {
  /*
  StmtList:
          %empty { $$ = 0; }
          | Stmt StmtList
  */
  auto t = stmtList;
  while (t != nullptr) {
    genStmt(t->child[0]);
    t = t->child[1];
  }
}

void IRGenerator::genStmt(pASTNode node) {
  /*
 Stmt: Exp SEMI
     | CompSt
     | RETURN Exp SEMI
     | IF LP Exp RP Stmt
     | IF LP Exp RP Stmt ELSE Stmt
     | WHILE LP Exp RP Stmt
 */
  if (node->child_count == 1) {
    // CompSt
    genCompSt(node->child[0]);
  } else if (node->child_count == 2) {
    // Exp SEMI
    Operand op = codes.newTemp();
    genExp(node->child[0], &op);
  } else if (node->child_count == 3) {
    // RETURN Exp SEMI
    auto t1 = codes.newTemp();
    genExp(node->child[1], &t1);
    codes.genIRCode(IR_RETURN, {t1});
  } else if (node->child_count == 7) {
    // IF LP Exp RP Stmt ELSE Stmt
    auto exp = node->child[2];
    auto stmt = node->child[4];
    auto label1 = codes.newLabel();
    auto label2 = codes.newLabel();

    genCond(exp, &label1, &label2);
    codes.genIRCode(IR_LABEL, {label1});
    genStmt(stmt);
    auto label3 = codes.newLabel();
    codes.genIRCode(IR_GOTO, {label3});
    codes.genIRCode(IR_LABEL, {label2});
    genStmt(node->child[6]);
    codes.genIRCode(IR_LABEL, {label3});
  } else {
    if (!strcmp(node->child[0]->name, "IF")) {
      // IF LP Exp RP Stmt
      auto exp = node->child[2];
      auto stmt = node->child[4];
      auto label1 = codes.newLabel();
      auto label2 = codes.newLabel();

      genCond(exp, &label1, &label2);
      codes.genIRCode(IR_LABEL, {label1});
      genStmt(stmt);
      codes.genIRCode(IR_LABEL, {label2});
    } else {
      // WHILE
      auto label1 = codes.newLabel();
      auto label2 = codes.newLabel();
      auto label3 = codes.newLabel();
      codes.genIRCode(IR_LABEL, {label1});
      genCond(node->child[2], &label2, &label3);
      codes.genIRCode(IR_LABEL, {label2});
      genStmt(node->child[4]);
      codes.genIRCode(IR_GOTO, {label1});
      codes.genIRCode(IR_LABEL, {label3});
    }
  }
}

void IRGenerator::genDef(pASTNode def) {
  /*
   Def: Specifier DecList SEMI
   DecList: Dec
     | Dec COMMA DecList
   Dec: VarDec
   | VarDec ASSIGNOP AssignmentExp
   VarDec: ID
     | VarDec LB INT RB
  */
  auto declist = def->child[1];
  bool flag = true;
  while (flag) {
    if (declist->child_count == 1) {
      flag = false;
    }
    auto dec = declist->child[0];
    genDec(dec);
    if (flag) {
      declist = declist->child[2];
    }
  }
}

void IRGenerator::genDec(pASTNode dec) {
  /* Dec: VarDec
       | VarDec ASSIGNOP AssignmentExp
     VarDec: ID
       | VarDec LB INT RB
   */
  auto vardec = dec->child[0];
  if (dec->child_count == 1) {
    genVarDec(vardec, nullptr);
  } else {
    // Exp process here
    Operand t1, t2;
    genVarDec(vardec, &t1);
    t2 = codes.newTemp();
    genExp(dec->child[2], &t2);
    codes.genIRCode(IR_ASSIGN, {t1, t2});
  }
}

void IRGenerator::genVarDec(pASTNode vardec, Operand *op) {
  if (vardec->child_count == 1) {
    auto fd = this->sym.find(vardec->child[0]->val);
    auto type = fd->second.type;
    if (type.k == Kind::Basic) {
      if (op) {
        op->kind = OP_VARIABLE;
        op->name = fd->first;
      }
    } else if (type.k == Kind::Array) {
      auto size = type.size();
      codes.genIRCode(
          IR_DEC, {Operand(OP_VARIABLE, fd->first), Operand(OP_SIZE, size)});
    } else if (type.k == Kind::Structure) {
      auto size = type.size();
      codes.genIRCode(
          IR_DEC, {Operand(OP_VARIABLE, fd->first), Operand(OP_SIZE, size)});
    }
  } else {
    genVarDec(vardec->child[0], op);
  }
}

void IRGenerator::genExp(pASTNode exp, Operand *place) {
  // Exp -> Exp ASSIGNOP Exp
  //      | Exp AND Exp
  //      | Exp OR Exp
  //      | Exp RELOP Exp
  //      | Exp PLUS Exp
  //      | Exp MINUS Exp
  //      | Exp STAR Exp
  //      | Exp DIV Exp
  //      | LP Exp RP
  //      | MINUS Exp
  //      | NOT Exp
  //      | ID LP Args RP
  //      | ID LP RP
  //      | Exp LB Exp RB
  //      | Exp DOT ID
  //      | ID
  //      | INT
  //      | FLOAT

  if (exp->child_count == 1) {
    auto name = exp->child[0]->name;
    if (!strcmp(name, "ID")) {
      auto fd = this->sym.find(exp->child[0]->val);
      place->kind = OP_VARIABLE;
      place->name = fd->first;
      for (const auto &item : this->funcs) {
        for (const auto &field : item.second.fields) {
          if (!strcmp(field.name.c_str(), fd->first.c_str())) {
            if (fd->second.type.k == Structure || fd->second.type.k == Array) {
              //函数参数中的结构体和数组都是传输地址
              place->kind = OP_ADDRESS;
            }
          }
        }
      }
    } else if (!strcmp(name, "INT")) {
      place->kind = OP_CONSTANT;
      place->value = getINTValue(exp->child[0]);
    } else if (!strcmp(name, "FLOAT")) {
      std::cerr << "Cannot translate float constant\n";
    } else {
      UNREACHABLE;
    }
  } else if (exp->child_count == 2) {
    // MINUS Exp
    // NOT Exp
    auto name = exp->child[0]->name;
    if (!strcmp(name, "MINUS")) {
      if (exp->child[1]->child[0]->type == NodeType::tokINT) {
        // 如果为常数就优化为- constant
        *place = Operand(OP_CONSTANT, -getINTValue(exp->child[1]->child[0]));
      } else {
        Operand t1 = codes.newTemp();
        genExp(exp->child[1], &t1);
        Operand zero = Operand(OP_CONSTANT, 0);
        codes.genIRCode(IR_SUB, {*place, zero, t1});
      }
    } else {
      // NOT
      auto label1 = codes.newLabel();
      auto label2 = codes.newLabel();
      auto trueNum = Operand(OP_CONSTANT, 1);
      auto falseNum = Operand(OP_CONSTANT, 0);
      codes.genIRCode(IR_ASSIGN, {*place, falseNum});
      genCond(exp, &label1, &label2);
      codes.genIRCode(IR_LABEL, {label1});
      codes.genIRCode(IR_ASSIGN, {*place, trueNum});
    }
  } else if (exp->child_count == 3) {
    auto name1 = exp->child[0]->name;
    auto name2 = exp->child[1]->name;
    auto name3 = exp->child[2]->name;

    if (!strcmp(name1, "Exp") && !strcmp(name3, "Exp")) {
      if (!strcmp(name2, "ASSIGNOP")) {
        Operand t2 = codes.newTemp();
        genExp(exp->child[2], &t2);
        Operand t1 = codes.newTemp();
        genExp(exp->child[0], &t1);
        codes.genIRCode(IR_ASSIGN, {t1, t2});
      } else if (!strcmp(name2, "AND") || !strcmp(name2, "OR") ||
                 !strcmp(name2, "RELOP")) {
        auto label1 = codes.newLabel();
        auto label2 = codes.newLabel();
        auto trueNum = Operand(OP_CONSTANT, 1);
        auto falseNum = Operand(OP_CONSTANT, 0);
        codes.genIRCode(IR_ASSIGN, {*place, falseNum});
        genCond(exp, &label1, &label2);
        codes.genIRCode(IR_LABEL, {label1});
        codes.genIRCode(IR_ASSIGN, {*place, trueNum});
      } else if (!strcmp(name2, "PLUS")) {
        auto t1 = codes.newTemp();
        genExp(exp->child[0], &t1);
        auto t2 = codes.newTemp();
        genExp(exp->child[2], &t2);
        codes.genIRCode(IR_ADD, {*place, t1, t2});
      } else if (!strcmp(name2, "MINUS")) {
        auto t1 = codes.newTemp();
        genExp(exp->child[0], &t1);
        auto t2 = codes.newTemp();
        genExp(exp->child[2], &t2);
        codes.genIRCode(IR_SUB, {*place, t1, t2});
      } else if (!strcmp(name2, "STAR")) {
        auto t1 = codes.newTemp();
        genExp(exp->child[0], &t1);
        auto t2 = codes.newTemp();
        genExp(exp->child[2], &t2);
        codes.genIRCode(IR_MUL, {*place, t1, t2});
      } else if (!strcmp(name2, "DIV")) {
        auto t1 = codes.newTemp();
        genExp(exp->child[0], &t1);
        auto t2 = codes.newTemp();
        genExp(exp->child[2], &t2);
        codes.genIRCode(IR_DIV, {*place, t1, t2});
      } else {
        UNREACHABLE;
      }
    } else if (!strcmp(name2, "Exp")) {
      // LP Exp RP
      genExp(exp->child[1], place);
    } else if (!strcmp(name2, "LP")) {
      // ID LP RP
      // function call
      if (!strcmp(exp->child[0]->val, "read")) {
        codes.genIRCode(IR_READ, {*place});
      } else {
        Operand func = Operand(OP_FUNCTION, exp->child[0]->val);
        if (place) {
          codes.genIRCode(IR_CALL, {*place, func});
        } else {
          auto temp = codes.newTemp();
          codes.genIRCode(IR_CALL, {temp, func});
        }
      }
    } else {
      // Exp DOT ID
      auto temp = codes.newTemp();
      genExp(exp->child[0], &temp);
      auto type = expType(exp->child[0]);
      Operand target;
      if (temp.kind == OP_ADDRESS) {
        target = Operand(OP_ADDRESS, temp.name);
      } else {
        target = codes.newTemp();
        codes.genIRCode(IR_GET_ADDR, {target, temp});
      }
      int offset = 0;
      for (const auto &item : type.structure.fields) {
        if (!strcmp(item.name.c_str(), exp->child[2]->val)) {
          break;
        } else {
          offset += item.type.size();
        }
      }
      Operand op_offset = Operand(OP_CONSTANT, offset);
      if (place) {
        InterCode newCode;
        newCode.genInterCode(IR_ADD, {*place, target, op_offset});
        codes.codes.push_back(newCode);
        // 对于操作ADDR加减的手动构造
        place->kind = OP_ADDRESS;
      }
    }
  } else {
    if (!strcmp(exp->child[0]->name, "ID")) {
      // Exp -> ID LP Args RP
      /* Args:
         AssignmentExp
           | Args COMMA AssignmentExp
      */
      Operand func = Operand(OP_FUNCTION, exp->child[0]->val);
      auto args = exp->child[2];
      std::vector<Type> types;
      std::vector<Operand> ops;
      bool flag = true;
      while (flag) {
        if (args->child_count == 1) {
          flag = false;
        }
        auto assignmentExp = args->child[0];
        if (flag) {
          assignmentExp = args->child[2];
        }
        auto temp = codes.newTemp();
        genExp(assignmentExp, &temp);
        // 这里获取到ADDRESS只有可能是数组或者结构体取值了，判断，然后取值到temp
        // 忽略传子结构体的情况
        if (temp.kind == OP_ADDRESS) {
          auto val = codes.newTemp();
          codes.genIRCode(IR_READ_ADDR, {val, temp});
          temp = val;
        }
        ops.push_back(temp);
        types.push_back(expType(assignmentExp));
        if (flag) {
          args = args->child[0];
        }
      }
      if (!strcmp(exp->child[0]->val, "write")) {
        codes.genIRCode(IR_WRITE, {ops[0]});
      } else {
        for (int i = 0; i < types.size(); ++i) {
          if (types[i].k == Structure || types[i].k == Array) {
            Operand varTemp = codes.newTemp();
            codes.genIRCode(IR_GET_ADDR, {varTemp, ops[i]});
            codes.genIRCode(IR_ARG, {varTemp});
          } else {
            codes.genIRCode(IR_ARG, {ops[i]});
          }
        }
        if (place) {
          codes.genIRCode(IR_CALL, {*place, func});
        } else {
          auto retTemp = codes.newTemp();
          codes.genIRCode(IR_CALL, {retTemp, func});
        }
      }
    } else {
      // Exp -> Exp LB Exp RB
      auto index = codes.newTemp();
      genExp(exp->child[2], &index);
      Operand base = codes.newTemp();
      genExp(exp->child[0], &base);
      Operand target;
      if (base.kind == OP_VARIABLE) {
        // 这里是直接就是变量，需要把地址取出来
        target = codes.newTemp();
        codes.genIRCode(IR_GET_ADDR, {target, base});
      } else {
        target = base;
      }

      auto type = expType(exp->child[0]);
      auto width = type.array.t->size();
      for (int i = 0; i < type.array.dim - 1; ++i) {
        width *= type.array.dims[i];
      }
      auto width_op = Operand(OpKind::OP_CONSTANT, width);
      auto offset = codes.newTemp();
      codes.genIRCode(IR_MUL, {offset, index, width_op});
      if (place) {
        InterCode newCode;
        newCode.genInterCode(IR_ADD, {*place, target, offset});
        codes.codes.push_back(newCode);
        // 对于操作ADDR加减的手动构造
        place->kind = OP_ADDRESS;
      }
    }
  }
}

void IRGenerator::genCond(pASTNode exp, Operand *labelTrue,
                          Operand *labelFalse) {
  // Exp -> Exp AND Exp
  //      | Exp OR Exp
  //      | Exp RELOP Exp
  //      | NOT Exp

  if (exp->child_count >= 2) {
    auto name1 = exp->child[0]->name;
    auto name2 = exp->child[1]->name;
    if (!strcmp(name2, "AND")) {
      auto label1 = codes.newLabel();
      genCond(exp->child[0], &label1, labelFalse);
      codes.genIRCode(IR_LABEL, {label1});
      genCond(exp->child[2], labelTrue, labelFalse);
    } else if (!strcmp(name2, "OR")) {
      auto label1 = codes.newLabel();
      genCond(exp->child[0], labelTrue, &label1);
      codes.genIRCode(IR_LABEL, {label1});
      genCond(exp->child[2], labelTrue, labelFalse);
    } else if (!strcmp(name2, "RELOP")) {
      auto t1 = codes.newTemp();
      auto t2 = codes.newTemp();
      genExp(exp->child[0], &t1);
      genExp(exp->child[2], &t2);
      auto relop = Operand(OP_RELOP, exp->child[1]->val);

      if (t1.kind == OP_ADDRESS) {
        auto temp = codes.newTemp();
        codes.genIRCode(IR_READ_ADDR, {temp, t1});
        t1 = temp;
      }
      if (t2.kind == OP_ADDRESS) {
        auto temp = codes.newTemp();
        codes.genIRCode(IR_READ_ADDR, {temp, t2});
        t2 = temp;
      }
      codes.genIRCode(IR_IF_GOTO, {t1, relop, t2, *labelTrue});
      codes.genIRCode(IR_GOTO, {*labelFalse});
    } else if (!strcmp(name1, "NOT")) {
      genCond(exp, labelFalse, labelTrue);
    } else {
      auto t1 = codes.newTemp();
      genExp(exp, &t1);
      auto t2 = Operand(OP_CONSTANT, 0);
      auto relop = Operand(OP_RELOP, "!=");
      if (t1.kind == OP_ADDRESS) {
        auto temp = codes.newTemp();
        codes.genIRCode(IR_READ_ADDR, {temp, t1});
        t1 = temp;
      }
      codes.genIRCode(IR_IF_GOTO, {t1, relop, t2, *labelTrue});
      codes.genIRCode(IR_GOTO, {*labelFalse});
    }
  } else {
    auto t1 = codes.newTemp();
    genExp(exp, &t1);
    auto t2 = Operand(OP_CONSTANT, 0);
    auto relop = Operand(OP_RELOP, "!=");
    if (t1.kind == OP_ADDRESS) {
      auto temp = codes.newTemp();
      codes.genIRCode(IR_READ_ADDR, {temp, t1});
      t1 = temp;
    }
    codes.genIRCode(IR_IF_GOTO, {t1, relop, t2, *labelTrue});
    codes.genIRCode(IR_GOTO, {*labelFalse});
  }
}

Type IRGenerator::expType(pASTNode exp) {
  // Exp -> Exp ASSIGNOP Exp
  //      | Exp AND Exp
  //      | Exp OR Exp
  //      | Exp RELOP Exp
  //      | Exp PLUS Exp
  //      | Exp MINUS Exp
  //      | Exp STAR Exp
  //      | Exp DIV Exp
  //      | LP Exp RP
  //      | MINUS Exp
  //      | NOT Exp
  //      | ID LP Args RP
  //      | ID LP RP
  //      | Exp LB Exp RB
  //      | Exp DOT ID
  //      | ID
  //      | INT
  //      | FLOAT
  if (exp->child_count == 1) {
    auto name = exp->child[0]->name;
    if (!strcmp(name, "ID")) {
      auto fd = this->sym.find(exp->child[0]->val);
      return fd->second.type;
    } else if (!strcmp(name, "INT")) {
      Type t;
      t.k = Basic;
      t.basic = Int;
      return t;
    } else if (!strcmp(name, "FLOAT")) {
      Type t;
      t.k = Basic;
      t.basic = Float;
      return t;
    } else {
      UNREACHABLE;
    }
  } else if (exp->child_count == 2) {
    // MINUS Exp
    // NOT Exp
    return expType(exp->child[1]);
  } else if (exp->child_count == 3) {
    auto name1 = exp->child[0]->name;
    auto name2 = exp->child[1]->name;
    auto name3 = exp->child[2]->name;

    if (!strcmp(name1, "Exp") && !strcmp(name3, "Exp")) {
      return expType(exp->child[0]);
    } else if (!strcmp(name2, "Exp")) {
      // LP Exp RP
      return expType(exp->child[1]);
    } else if (!strcmp(name2, "LP")) {
      // ID LP RP
      // function call
      auto fd = this->funcs.find(exp->child[0]->val);
      return fd->second.ret_type;
    } else {
      // Exp DOT ID
      auto type = expType(exp->child[0]);
      auto fs = type.structure.fields;
      for (const auto &item : fs) {
        if (!strcmp(item.name.c_str(), exp->child[2]->val)) {
          return item.type;
        }
      }
    }
  } else {
    if (!strcmp(exp->child[0]->name, "ID")) {
      // Exp -> ID LP Args RP
      auto fd = this->funcs.find(exp->child[0]->val);
      return fd->second.ret_type;
    } else {
      // Exp -> Exp LB Exp RB
      auto type = expType(exp->child[0]);
      if (type.array.dim == 1) {
        return *type.array.t;
      } else {
        type.array.dim -= 1;
        return type;
      }
    }
  }
}

Operand InterCodeList::newTemp() {
  Operand op;
  op.kind = OpKind::OP_VARIABLE;
  std::stringstream ss;
  ss << "t" << tempVarNumber;
  op.name = ss.str();
  tempVarNumber += 1;
  return op;
}

Operand InterCodeList::newLabel() {
  Operand op;
  op.kind = OpKind::OP_LABEL;
  std::stringstream ss;
  ss << "label" << labelNumber;
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
