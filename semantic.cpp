#include "semantic.h"
#include "ast.h"
#include <cstring>
#include <iostream>

bool Type::eq(Type &other) {
  if (this->k != other.k) {
    return false;
  }
  if (this->k == Basic) {
    return this->basic == other.basic;
  }
  if (this->k == Array) {
    return this->array.dim == other.array.dim &&
           this->array.t->eq(*other.array.t);
  }
  if (this->k == Structure) {
    bool flag = true;
    if (this->structure.fields.size() != other.structure.fields.size()) {
      return false;
    }
    for (size_t i = 0; i < this->structure.fields.size(); i++) {
      if (!this->structure.fields[i].type.eq(other.structure.fields[i].type)) {
        flag = false;
      }
    }
    return flag;
  }
  std::cout << "UnExpteced Type!!\n";
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
        if (fd == this->structTable.end()) {
          this->structTable.insert({t.structure.structName, t});
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
      if (!strcmp(node->child[2]->name, "SEMI")) {
        // Spec FunDec SEMI
      } else {
        // Spec FunDec CompSt
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
        std::string name;
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
      
    } else {
    }

    if (flag) {
      extdeclist = extdeclist->child[2];
    }
  }
}
