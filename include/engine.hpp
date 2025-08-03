#pragma once
#include "column.hpp"
#include "json.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <system_error>
#include <variant>
#include <vector>
using json = nlohmann::json;
using namespace std;

class engine {
private:
  bool tableExists(const string &name) {
    filesystem::path path = "db/tables/" + name + ".meta";
    return filesystem::exists(path);
  }

  bool openMetaFile(const string &name, fstream &file) {
    if (file.is_open()) {
      cout << "A file is already opened";
      return false;
    }
    if (!tableExists(name)) {
      return false;
    }
    file.open("db/tables/" + name + ".meta", ios::app | ios::in);
    if (!file.is_open()) {
      return false;
    }
    return true;
  }

  bool writeMeta(const string &name, const vector<column> &columns,
                 const column &primaryKey) {


    fstream file;
    if(!openMetaFile(name,file)) return false;
    json j;
    j["table_name"] = name;

    for (auto &col : columns) {
      bool is_primary = (col.name == primaryKey.name);
      j["columns"].push_back(
          {{"name", col.name},
           {"type", col.type},
           {"size", col.size},
           {"is_indexed", is_primary ? true : col.isIndexed}});
    }

    j["primary_key"] = primaryKey.name;
    fstream file;
    openMetaFile(name,file);
    file << j.dump(4);
    file.close();
    return true;
  }

  bool createColumnFiles(const string &name, const vector<column> &columns) {
    string path = "db/data/" + name;
    error_code ec;
    filesystem::create_directory(path, ec);
    if (ec)
      return false;
    for (auto &col : columns) {
      string filePath = path + "/" + col.name + ".bin";
      std::ofstream file(filePath, std::ios::binary);
      if (!file.is_open())
        return false;
      file.close();
    }
    return true;
  }

  vector<ofstream> openColumnFiles(const string &tableName,
                                   const vector<column> &columns) {
    vector<ofstream> files;
    for (const auto &col : columns) {
      ofstream file("db/data/" + tableName + "/" + col.name + ".bin");
      if (!file.is_open()) {
        cout << "Error opening column file" << endl;
        return {};
      }
      files.push_back(std::move(file));
    }
    return files;
  }

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
