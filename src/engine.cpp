#include "Result.hpp"
#include "json.hpp"
#include <engine.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>
using json = nlohmann::json;

// Private Helper functions

bool Engine::tableExists(const string &name) {
  filesystem::path path = filesystem::path("db") / "tables" / (name + ".meta");
  return filesystem::exists(path);
}

Res<fstream> Engine::openMetaFile(const string &name) {
  filesystem::path path = filesystem::path("db") / "tables" / (name + ".meta");
  fstream file = fstream(path, ios::in | ios::out);

  if (!file.is_open())
    return {std::move(file), "Opening File Failed"};

  return {std::move(file)};
}

bool Engine::writeMeta(const string &name, const vector<column> &columns) {

  json j;
  bool isPrimaryKeySet = false;
  j["table_name"] = name;

  for (auto &col : columns) {
    j["columns"].push_back({{"name", col.name},
                            {"type", col.type},
                            {"size", col.size},
                            {"is_indexed", col.isIndexed},
                            {"is_unique", col.isUnique},
                            {"is_primary_key", col.isPrimaryKey}});
    if (col.isPrimaryKey) {
      if (isPrimaryKeySet) {
        cout << "Only one Primary key accepted";
        return false;
      }
      isPrimaryKeySet = true;
      j["primary_key"] = col.name;
    }
  }

  fstream file;
  if (!openMetaFile(name, file))
    return false;
  file << j.dump(4);
  if (file.fail()) {
    cout << "Failed to write json data to file";
    return false;
  }
  file.close();
  return true;
}

bool Engine::createColumnFiles(const string &name,
                               const vector<column> &columns) {
  // string path = "db/data/" + name;
  filesystem::path path = filesystem::path("db") / "data" / name;
  error_code ec;
  filesystem::create_directory(path, ec);
  if (ec) {
    cout << "Some error while creating directory" << endl;
    return false;
  }
  for (auto &col : columns) {
    filesystem::path filePath = path / (col.name + ".bin");
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
      cout << "Error creating column file:" << col.name << ".col" << endl;
      return false;
    }
    file.close();
  }
  return true;
}

// bool Engine::openColumnFiles(const string &name, vector<fstream> &files,
//                              const vector<column> &columns) {
//   if (!tableExists(name))
//     return false;
//   filesystem::path tableDir = filesystem::path("db") / "data" / name;
//   fstream file;
//   for (auto &col : columns) {
//     filesystem::path fileName = tableDir / (col.name + ".col");
//     file.open(fileName, ios::app | ios::binary);
//     if (!file.is_open())
//       return false;
//     files.push_back(file);
//     file.close();
//   }
//   return true;
// }

Res<None> Engine::createMetaFile(const string &name) {
  ofstream file(filesystem::path("db") / "tables" / (name + ".meta"));
  if (!file.is_open()) {
    return {None{}, "Failed Creating file"};
  }
  file.close();
  return {None{}};
}

bool Engine::loadColumns(const string &name, vector<column> &columns) {
  fstream file;
  if (!openMetaFile(name, file))
    return false;
  json j;
  file >> j;
  cout << j["table_name"];
  cout << endl;
  cout << j;
  return true;
}

// Public functions

bool Engine::createTable(const string &name, const vector<column> &columns,
                         const column &primaryKey) {
  // check if a table with that name already exists
  if (!createMetaFile(name))
    return false;
  // writing the metadata
  if (!writeMeta(name, columns)) {
    cout << "Failed to write metadata for " << name << ".meta file" << endl;
    return false;
  }
  // creating columnfiles
  return createColumnFiles(name, columns);
}

bool Engine::insertIntoTable(const string &name, const vector<string> &vec) {
  if (tableExists(name)) {
    cout << "Table doesnt exist for inserting";
    return false;
  }
  for (auto v : vec) {
  }
  return false;
}
