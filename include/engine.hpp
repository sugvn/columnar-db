#pragma once
#include "column.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <system_error>
#include <variant>
#include <vector>
using json = nlohmann::json;
using namespace std;

class Engine {
private:
  bool tableExists(const string &name);

  bool openMetaFile(const string &name, fstream &file);

  bool writeMeta(const string &name, const vector<column> &columns,
                 const column &primaryKey);

  bool createColumnFiles(const string &name, const vector<column> &columns);

  vector<ofstream> openColumnFiles(const string &tableName,
                                   const vector<column> &columns);

public:
  bool createTable(const string &name, const vector<column> &columns,
                   const column &primaryKey) {
    // check if a table with that name already exists
    if (tableExists(name)) {
      cout << "Table with the name " << name << " exists" << endl;
      return false;
    }
    // creating a file using ofstream
    ofstream meta("db/tables/" + name + ".meta");
    if (!meta.is_open()) {
      cout << "Failed to open file " << name << ".meta";
      return false;
    }
    // writing the metadata
    if (!writeMeta(name, meta, columns, primaryKey)) {
      cout << "Failed to write metadata for " << name << ".meta file" << endl;
      return false;
    }
    // creating columnfiles
    return createColumnFiles(name, columns);
  }

  bool insertIntoTable(const string &name,
                       const vector<variant<int, bool, string>> &vec) {
    if (!tableExists(name)) {
      cout << "Table doesnt exist for inserting";
      return false;
    }
    for (auto v : vec) {
    }
    return false;
  }
};
