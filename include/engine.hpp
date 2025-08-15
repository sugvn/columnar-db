#pragma once
#include "Result.hpp"
#include "column.hpp"
#include <fstream>
#include <string>
#include <variant>
#include <vector>
using std::string;
using std::vector;
using None=std::monostate;

class Engine {

private:
  bool tableExists(const string &name);
  Res<fstream> openMetaFile(const string &name);
  Res<None> writeMeta(fstream &file, const vector<Column> &columns);
  Res<None> createColumnFiles(const string &name, const vector<Column> &columns);
  Res<None> createMetaFile(const string &name);
  Res<vector<fstream>> openColumnFiles(const string &tableName,const vector<Column> &cols);

public:
  bool createTable(const string &name, const vector<Column> &columns,const Column &primaryKey);
  bool loadColumns(const string &name, vector<Column> &columns);
  bool insertIntoTable(const string &name, const vector<string> &vec);

};
