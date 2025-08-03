#pragma once
#include <stdexcept>
#include <string>
#include <unordered_map>

enum class Type {
  INT,
  BOOL,
  STRING,
};

inline Type stringToType(const std::string &type) {
  if (type == "string") {
    return Type::STRING;
  }
  if (type == "bool") {
    return Type::BOOL;
  }
  if (type == "int") {
    return Type::INT;
  }
  throw std::invalid_argument("unknown type:" + type);
}

inline const std::unordered_map<Type, int> typeSize = {
    {Type::INT, 4}, {Type::STRING, 15}, {Type::BOOL, 1}};

struct column {
  std::string name;
  Type type;
  int size;
  bool isIndexed;
  bool isPrimaryKey;
  bool isUnique;

  column(const std::string &n, const std::string &t,int s=0, bool i = false,bool u=false, bool pk = false):
        name(n),
        type(stringToType(t)),
        size(s!=0?s:typeSize.at(type)),
        isIndexed(pk || i),
        isUnique(pk || u),
        isPrimaryKey(pk) {}
    
  column() = default;
};
