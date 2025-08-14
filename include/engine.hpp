#pragma once
#include "Result.hpp"
#include "column.hpp"
#include "error.hpp"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Engine {

private:
  bool tableExists(const string &name);
  Res<fstream> openMetaFile(const string &name);
  void writeMeta(const string &name, const vector<column> &columns);
  void createColumnFiles(const string &name, const vector<column> &columns,Err *e=nullptr);
  void createMetaFile(const string &name,Err *e=nullptr);
  void openColumnFiles(const string &tableName, vector<fstream> &files,const vector<column> &cols,Err *e=nullptr);

public:
  bool createTable(const string &name, const vector<column> &columns,const column &primaryKey);
  bool loadColumns(const string &name, vector<column> &columns);
  bool insertIntoTable(const string &name, const vector<string> &vec);

};
