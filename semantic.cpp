#include "semantic.h"
#include "ast.h"
#include <cstring>
#include <iostream>
#include <memory>

bool Type::eq(Type &other) {
  if (this->k != other.k) {
    return false;
  }
  if (this->k == Error) {
    return true;
  }
  if (this->k == Basic) {
    return this->basic == other.basic;
  }
  if (this->k == Array) {
    return this->array.dim == other.array.dim &&
           this->array.t->eq(*other.array.t);
  }
  if (this->k == Structure) {
    if (this->structure.fields.size() != other.structure.fields.size()) {
      return false;
    }
    for (size_t i = 0; i < this->structure.fields.size(); i++) {
      if (!this->structure.fields[i].type.eq(other.structure.fields[i].type)) {
        return false;
      }
    }
    return true;
  }
  UNREACHABLE;
  return true;
}

void SymTable::ExtDef(pASTNode node) {
  /*
        Specifier ExtDecList SEMI
      | Specifier SEMI
      | Specifier FunDec CompSt
      | Specifier FunDec SEMI
    */
  // process Specifier
  Type t = Specifier(node->child[0]);
  if (node->child_count == 2) {
    // the struct definition
    if (t.k == Structure) {
      if (!t.structure.unname) {
        auto fd = this->structTable.find(t.structure.structName);
        bool flag =
            this->structTable.find(t.structure.structName) ==
                this->structTable.end() &&
            this->fieldTableStack.front().find(t.structure.structName) ==
                this->fieldTableStack.front().end();
        if (flag) {
          this->structTable.insert({t.structure.structName, t});
        } else {
          std::string msg;
          msg.append("Conflict struct name");
          printSemanticError(DUPLICATED_NAME, node->lineNum, msg);
        }
      } else {
        // unname structure here is useless
        std::cerr << "Warning Useless Structure Definition at line: "
                  << node->lineNum << std::endl;
      }
    } else {
      UNREACHABLE;
    }
  } else {
    if (!strcmp(node->child[1]->name, "FunDec")) {
      auto func = FunDec(node->child[1]);
      if (!strcmp(node->child[2]->name, "SEMI")) {
        // Spec FunDec SEMI
        bool ret_type_error = (t.k == Kind::Error);
        if (ret_type_error || func.has_error) {
          // 忽略有错误的函数声明
          std::cerr << "Ignore function declarations with errors at Line"
                    << node->child[1]->lineNum << std::endl;
        } else {
          // 判断是否有重名的声明
          auto fd = this->functionTable.find(func.name);
          Function f;
          f.fields = func.fields;
          f.has_body = false;
          f.name = func.name;
          f.ret_type = t;
          if (fd == this->functionTable.end()) {
            // not found
            this->functionTable.insert({f.name, f});
          } else {
            // 有重名的，判断是否相同
            if (f.eq(fd->second)) {
              // 完全相同的声明重复出现
              std::cerr << "Warning same function declaration\n";
            } else {
              std::string msg;
              msg.append("Conflicting function declarations");
              printSemanticError(FUNC_MULTI_DEF, node->child[1]->lineNum, msg);
            }
          }
        }
      } else {
        // Spec FunDec CompSt
        bool ret_type_error = (t.k == Kind::Error);
        if (ret_type_error || func.has_error) {
          // 如果定义有错误就不去查重
          std::cerr << "Error detected, skipping declaration check"
                    << node->child[1]->lineNum << std::endl;
        } else {
          auto fd = this->functionTable.find(func.name);
          Function f;
          f.fields = func.fields;
          f.has_body = true;
          f.name = func.name;
          f.ret_type = t;
          if (fd == this->functionTable.end()) {
            // not found
            this->functionTable.insert({f.name, f});
          } else {
            // has same name
            if (f.eq(fd->second)) {
              // same declaration
              if (fd->second.has_body) {
                // 检测到之前有定义
                std::string msg;
                msg.append("Conflicting function definition");
                printSemanticError(REDEF_FUNC, node->child[1]->lineNum, msg);
              } else {
                fd->second.has_body = true;
              }
            } else {
              std::string msg;
              msg.append("Conflicting function definition");
              printSemanticError(FUNC_MULTI_DEF, node->child[1]->lineNum, msg);
            }
          }
          auto compst = node->child[2];
          // Process CompSt
          CompSt(compst, f);
        }
      }
    } else {
      // Spec ExtDecList SEMI
      // Global Variables Definition
      if (t.k != Kind::Error) {
        this->ExtDecList(node->child[1], &t);
      }
    }
  }
}

Type SymTable::Specifier(pASTNode node) {
  /*
     TYPE
   | StructSpecifier
   */
  Type t;
  auto child = node->child[0];
  if (!strcmp(child->name, "TYPE")) {
    t.k = Kind::Basic;
    if (!strcmp(child->val, "int")) {
      t.basic = BasicType::Int;
    } else {
      t.basic = BasicType::Float;
    }
  } else {
    return StructSpecifier(child);
  }
  return t;
}

Type SymTable::StructSpecifier(pASTNode node) {
  /*
   STRUCT OptTag LC DefList RC
   STRUCT Tag

   OptTag -> ID | e
   Tag -> ID
  */
  Type t;
  auto tag = node->child[1];
  if (tag == nullptr) {
    // OptTag -> Empty
    // STRUCT nullptr LC DefList RC
    // unname struct
    t.k = Kind::Structure;
    t.structure.structName = "";
    t.structure.unname = true;
    DefList_Struct(node->child[3], &t);
  } else if (!strcmp(tag->name, "Tag")) {
    // STRUCT Tag
    auto struct_name = std::string(tag->child[0]->val);
    auto fd = this->structTable.find(struct_name);
    if (fd == this->structTable.end()) {
      // cannot find
      std::string msg;
      msg.append("Undefined structure: ");
      msg.append(tag->child[0]->val);
      printSemanticError(UNDEF_STRUCT, tag->lineNum, msg);
      t.k = Kind::Error;
    } else {
      t = fd->second;
    }
  } else {
    // STRUCT OptTag LC DefList RC
    t.k = Kind::Structure;
    t.structure.structName = tag->child[0]->val;
    t.structure.unname = false;
    DefList_Struct(node->child[3], &t);
  }
  return t;
}

void SymTable::DefList_Struct(pASTNode node, Type *type) {
  /*
   DefList:
     %empty
     | Def DefList
   Def: Specifier DecList SEMI
   DecList: Dec
     | Dec COMMA DecList
   Dec: VarDec
   | VarDec ASSIGNOP AssignmentExp
   VarDec: ID
     | VarDec LB INT RB
  */
  auto t = node;
  while (t != nullptr) {
    Def_Struct(t->child[0], type);
    t = t->child[1];
  }
}

void SymTable::Def_Struct(pASTNode node, Type *type) {
  auto spec = Specifier(node->child[0]);
  auto declist = node->child[1];
  bool flag = true;
  while (flag) {
    /* type->structure.fields */
    if (declist->child_count == 1) {
      flag = false;
    }
    auto dec = declist->child[0];
    if (dec->child_count != 1) {
      std::string msg;
      msg.append("Initializing variables in a structure");
      printSemanticError(REDEF_FEILD, dec->lineNum, msg);
    } else {
      auto vardec = dec->child[0];
      if (vardec->child_count == 1) {
        // VarDec -> ID
        if (!isNameExists(type->structure.fields, vardec->child[0]->val)) {
          Field f;
          f.name = vardec->child[0]->val;
          f.type = spec;
          type->structure.fields.push_back(f);
        } else {
          // the name already exists
          std::string msg;
          msg.append("Duplicate definition in structure");
          printSemanticError(REDEF_FEILD, vardec->lineNum, msg);
        }
      } else {
        // VarDec -> VarDec LB INT RB
        std::vector<int> dimesions;
        uint32_t size = 1;
        while (vardec->child_count != 1) {
          int dim = getINTValue(vardec->child[2]);
          dimesions.push_back(dim);
          size *= dim;
          vardec = vardec->child[0];
        }
        if (!isNameExists(type->structure.fields, vardec->child[0]->val)) {
          Field f;
          Type arr_type;
          arr_type.k = Kind::Array;
          arr_type.array.dim = dimesions.size();
          arr_type.array.size = size;
          arr_type.array.t = std::make_shared<Type>();
          *(arr_type.array.t) = spec;
          f.type = arr_type;
          f.name = vardec->child[0]->val;
          type->structure.fields.push_back(f);
        } else {
          std::string msg;
          msg.append("Duplicate definition in structure (Array)");
          printSemanticError(REDEF_FEILD, vardec->lineNum, msg);
        }
      }
    }
    if (flag) {
      declist = declist->child[2];
    }
  }
}

void SymTable::ExtDecList(pASTNode extdeclist, Type *spec) {
  /*
   ExtDecList:
      VarDec
      | VarDec COMMA ExtDecList
   VarDec: ID
     | VarDec LB INT RB
  */
  bool flag = true;
  while (flag) {
    if (extdeclist->child_count == 1) {
      flag = false;
    }
    auto vardec = extdeclist->child[0];
    if (vardec->child_count == 1) {
      // VarDec -> ID
      if (!this->isVarNameExists(vardec->child[0]->val)) {
        Field f;
        f.name = vardec->child[0]->val;
        f.type = *spec;
        this->fieldTableStack.back().insert({f.name, f});
      } else {
        std::string msg;
        msg.append("Conflict name in global variables: ");
        msg.append(vardec->child[0]->val);
        printSemanticError(REDEF_VAR, vardec->lineNum, msg);
      }
    } else {
      // VarDec -> VarDec LB INT RB
      std::vector<int> dimesions;
      uint32_t size = 1;
      while (vardec->child_count != 1) {
        int dim = getINTValue(vardec->child[2]);
        dimesions.push_back(dim);
        size *= dim;
        vardec = vardec->child[0];
      }
      if (!this->isVarNameExists(vardec->child[0]->val)) {
        Field f;
        Type arr_type;
        arr_type.k = Kind::Array;
        arr_type.array.dim = dimesions.size();
        arr_type.array.size = size;
        arr_type.array.t = std::make_shared<Type>();
        *(arr_type.array.t) = *spec;
        f.type = arr_type;
        f.name = vardec->child[0]->val;
        this->fieldTableStack.back().insert({f.name, f});
      } else {
        std::string msg;
        msg.append("Conflict array name in global variables: ");
        msg.append(vardec->child[0]->val);
        printSemanticError(REDEF_VAR, vardec->lineNum, msg);
      }
    }

    if (flag) {
      extdeclist = extdeclist->child[2];
    }
  }
}

_FunDecInf SymTable::FunDec(pASTNode node) {
  /* FunDec: ID LP VarList RP
        | ID LP RP
    VarList:
       ParamDec COMMA VarList
       | ParamDec
    ParamDec:
        Specifier VarDec
    VarDec: ID
      | VarDec LB INT RB
    */
  std::string name = node->child[0]->val;
  _FunDecInf func;
  if (node->child_count == 4) {
    // process varlist
    auto varlist = node->child[2];
    bool flag = true;
    while (flag) {
      if (varlist->child_count == 1) {
        flag = false;
      }
      auto paramdec = varlist->child[0];
      auto spec = Specifier(paramdec->child[0]);
      auto vardec = paramdec->child[1];
      if (spec.k == Kind::Error) {
        func.has_error = true;
      }
      if (vardec->child_count == 1) {
        if (!isNameExists(func.fields, vardec->child[0]->val)) {
          Field f;
          f.name = vardec->child[0]->val;
          f.type = spec;
          func.fields.push_back(f);
        } else {
          func.has_error = true;
          std::string msg;
          msg.append("Conflict name in function parameters");
          printSemanticError(REDEF_VAR, vardec->lineNum, msg);
        }
      } else {
        std::vector<int> dimesions;
        uint32_t size = 1;
        while (vardec->child_count != 1) {
          int dim = getINTValue(vardec->child[2]);
          dimesions.push_back(dim);
          size *= dim;
          vardec = vardec->child[0];
        }
        if (!isNameExists(func.fields, vardec->child[0]->val)) {
          Field f;
          Type arr_type;
          arr_type.k = Kind::Array;
          arr_type.array.dim = dimesions.size();
          arr_type.array.size = size;
          arr_type.array.t = std::make_shared<Type>();
          *(arr_type.array.t) = spec;
          f.type = arr_type;
          f.name = vardec->child[0]->val;
          func.fields.push_back(f);
        } else {
          func.has_error = true;
          std::string msg;
          msg.append("Conflict name in function parameters (Array)");
          printSemanticError(REDEF_VAR, vardec->lineNum, msg);
        }
      }
      if (flag) {
        varlist = varlist->child[2];
      }
    }

  } else {
    // non parameters
    // do nothing
  }
  func.name = name;
  return func;
}

void SymTable::CompSt(pASTNode compst, const Function &func) {
  // LC DefList StmtList RC
  this->newFieldTable();
  // 这里将函数定义的变量直接放入当前FiledTable中
  for (auto f : func.fields) {
    this->fieldTableStack.back().insert({f.name, f});
  }
  DefList_CompSt(compst->child[1], func);
  this->popFieldTable();
}

void SymTable::DefList_CompSt(pASTNode node, const Function &func) {
  /*
   DefList:
     %empty
     | Def DefList
 */
  auto t = node;
  while (t != nullptr) {
    Def_CompSt(t->child[0], func);
    t = t->child[1];
  }
}

void SymTable::Def_CompSt(pASTNode node, const Function &func) {
  /*
     Def: Specifier DecList SEMI
     DecList: Dec
       | Dec COMMA DecList
     Dec: VarDec
     | VarDec ASSIGNOP AssignmentExp
     VarDec: ID
       | VarDec LB INT RB
  */
  auto spec = Specifier(node->child[0]);
  auto declist = node->child[1];
  bool flag = true;
  while (flag) {
    if (declist->child_count == 1) {
      flag = false;
    }
    auto dec = declist->child[0];
    auto vardec = dec->child[0];
    if (vardec->child_count == 1) {
      // VarDec -> ID
      // 检查函数定义的变量，以及当前变量域
      bool flag1 = isVarNameExists(vardec->child[0]->val);
      bool flag2 = isNameExists(func.fields, vardec->child[0]->val);
      if (flag1 || flag2) {
        std::string msg;
        msg.append("Duplicate definition of variable");
        printSemanticError(REDEF_VAR, vardec->lineNum, msg);
      } else {
        Field f;
        f.name = vardec->child[0]->val;
        f.type = spec;
        this->fieldTableStack.back().insert({f.name, f});
      }
    } else {
      // VarDec -> VarDec LB INT RB
      std::vector<int> dimesions;
      uint32_t size = 1;
      while (vardec->child_count != 1) {
        int dim = getINTValue(vardec->child[2]);
        dimesions.push_back(dim);
        size *= dim;
        vardec = vardec->child[0];
      }
      bool flag1 = isVarNameExists(vardec->child[0]->val);
      bool flag2 = isNameExists(func.fields, vardec->child[0]->val);
      if (flag1 || flag2) {
        std::string msg;
        msg.append("Duplicate definition of array variable");
        printSemanticError(REDEF_VAR, vardec->lineNum, msg);
      } else {
        Field f;
        Type arr_type;
        arr_type.k = Kind::Array;
        arr_type.array.dim = dimesions.size();
        arr_type.array.size = size;
        arr_type.array.t = std::make_shared<Type>();
        *(arr_type.array.t) = spec;
        f.type = arr_type;
        f.name = vardec->child[0]->val;
        this->fieldTableStack.back().insert({f.name, f});
      }
    }
    if (dec->child_count != 1) {
      auto assignmentexp = dec->child[2];
      // TODO: Process Exp Here
    } else {
    }
    if (flag) {
      declist = declist->child[2];
    }
  }
}

Type SymTable::Exp(pASTNode node) {
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
  Type error_type;
  error_type.k = Kind::Error;
  if (node->child_count == 1) {
    // ID | INT | FLOAT
    auto name = node->child[0]->name;
    if (!strcmp(name, "ID")) {
      auto find = findVar(node->child[0]->val);
      if (find.k == Kind::Error) {
        std::string msg;
        msg.append("Undefined Variables");
        printSemanticError(UNDEF_VAR, node->child[0]->lineNum, msg);
        return error_type;
      } else {
        return find;
      }
    } else if (!strcmp(name, "INT")) {
      Type t;
      t.k = Kind::Basic;
      t.basic = Int;
      return t;
    } else if (!strcmp(name, "FLOAT")) {
      Type t;
      t.k = Kind::Basic;
      t.basic = Float;
      return t;
    } else {
      UNREACHABLE;
      return error_type;
    }
  } else if (node->child_count == 2) {
    // MINUS Exp
    // NOT Exp
    auto name = node->child[0]->name;
    auto exp_type = Exp(node->child[1]);
    if (!strcmp(name, "MINUS")) {
      if (exp_type.k != Kind::Basic) {
        // Error
        std::string msg;
        msg.append("Cannot Apply MINUS to the type");
        printSemanticError(TYPE_MISMATCH_OP, node->child[0]->lineNum, msg);
        return error_type;
      } else {
        return exp_type;
      }
    } else {
      if (exp_type.k == Kind::Basic && exp_type.basic == BasicType::Int) {
        return exp_type;
      } else {
        std::string msg;
        msg.append("Cannot Apply NOT to the type");
        printSemanticError(TYPE_MISMATCH_OP, node->child[0]->lineNum, msg);
        return error_type;
      }
    }
  } else if (node->child_count == 3) {
    //  Exp -> Exp ASSIGNOP Exp
    //      | Exp AND Exp
    //      | Exp OR Exp
    //      | Exp RELOP Exp
    //      | Exp PLUS Exp
    //      | Exp MINUS Exp
    //      | Exp STAR Exp
    //      | Exp DIV Exp
    //      | LP Exp RP
    //      | ID LP RP
    //      | Exp DOT ID
    auto name1 = node->child[0]->name;
    auto name2 = node->child[1]->name;
    auto name3 = node->child[2]->name;

    if (!strcmp(name1, "Exp") && !strcmp(name3, "Exp")) {
      auto t1 = Exp(node->child[0]);
      auto t2 = Exp(node->child[2]);
      if (!strcmp(name2, "ASSIGNOP")) {
        // check left value
        auto lhs = node->child[0];
        bool is_lvalue =
            (lhs->child_count == 1 && !strcmp(lhs->child[0]->name, "ID")) ||
            (!strcmp(lhs->child[1]->name, "DOT")) ||
            (!strcmp(lhs->child[1]->name, "LB"));
        if (is_lvalue) {
          if (!t1.eq(t2)) {
            std::string msg;
            msg.append("Type mismatched for assignment exp");
            printSemanticError(TYPE_MISMATCH_ASSIGN, node->child[0]->lineNum,
                               msg);
            return error_type;
          } else {
            return t1;
          }
        } else {
          std::string msg;
          msg.append("Cannot Assign to a rvalue");
          printSemanticError(LEFT_VAR_ASSIGN, node->child[0]->lineNum, msg);
          return error_type;
        }
      } else if (!strcmp(name2, "AND") && !strcmp(name2, "OR")) {
        // must Integer Type
        if (!(t1.k == Basic && t2.k == Basic && t1.basic == Int &&
              t2.basic == Int)) {
          std::string msg;
          msg.append("Mismatched Type for AND/OR");
          printSemanticError(TYPE_MISMATCH_OP, node->child[0]->lineNum, msg);
          return error_type;
        } else {
          return t1;
        }
      } else if (!strcmp(name2, "RELOP")) {
        if (t1.k == Basic && t2.k == Basic && t1.basic == t2.basic) {
          // 关系运算完成后是Int类型
          Type ret;
          ret.k = Basic;
          ret.basic = Int;
          return ret;
        } else {
          std::string msg;
          msg.append("Mismatched Type for RELOP");
          printSemanticError(TYPE_MISMATCH_OP, node->child[0]->lineNum, msg);
          return error_type;
        }
      } else if (!strcmp(name2, "PLUS") || !strcmp(name2, "MINUS") ||
                 !strcmp(name2, "STAR") || !strcmp(name2, "DIV")) {
        if (t1.k == Basic && t2.k == Basic && t1.basic == t2.basic) { 
          return t1;
        } else {
        }
      } else {
        UNREACHABLE;
      }
    } else if (!strcmp(name2, "Exp")) {
      // LP Exp RP
    } else if (!strcmp(name2, "LP")) {
      // ID LP RP
    } else {
      // Exp DOT ID
    }
  }
}
