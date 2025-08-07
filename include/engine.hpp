#pragma once
#include "column.hpp"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Engine {

private:
  bool tableExists(const string &name);
  bool openMetaFile(const string &name, fstream &file);
  bool writeMeta(const string &name, const vector<column> &columns);
  bool createColumnFiles(const string &name, const vector<column> &columns);
  bool createMetaFile(const string &name);
  bool openColumnFiles(const string &tableName, vector<fstream> &files,const vector<column> &cols);

public:
  bool createTable(const string &name, const vector<column> &columns,const column &primaryKey);
  bool loadColumns(const string &name, vector<column> &columns);
  bool insertIntoTable(const string &name, const vector<string> &vec);

};
