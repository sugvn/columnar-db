#pragma once
#include <string>

enum class Type { INT, BOOL, STRING, UNKNOWN };

// inline Type stringToType(const std::string &type) {
//   if (type == "string") {
//     return Type::STRING;
//   }
//   if (type == "bool") {
//     return Type::BOOL;
//   }
//   if (type == "int") {
//     return Type::INT;
//   }
//   return Type::UNKNOWN;
// }
//
// inline const std::unordered_map<Type, int> typeSize = {
//     {Type::INT, 4}, {Type::STRING, 15}, {Type::BOOL, 1}};

struct Column {
  std::string name;
  Type type;
  int size;
  bool isIndexed;
  bool isPrimaryKey;
  bool isUnique;
  Column(const std::string &n, Type &t, int s, bool isI, bool isP, bool isU)
      : name(n), type(t), size(s), isIndexed(isI), isPrimaryKey(isP),
        isUnique(isU) {}
};
