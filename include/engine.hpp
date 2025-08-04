#pragma once
#include "column.hpp"
#include <fstream>
#include <string>
#include <variant>
#include <vector>
using namespace std;

class Engine {
private:
  bool tableExists(const string &name);

  bool openMetaFile(const string &name, fstream &file);

  bool writeMeta(const string &name, const vector<column> &columns);
  bool createColumnFiles(const string &name, const vector<column> &columns);
  bool createMetaFile(const string &name);

  vector<ofstream> openColumnFiles(const string &tableName,
                                   const vector<column> &columns);

public:
  bool createTable(const string &name, const vector<column> &columns,
                   const column &primaryKey) ;

  bool insertIntoTable(const string &name,
                       const vector<variant<int, bool, string>> &vec);
};
