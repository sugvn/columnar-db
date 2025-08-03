#include <engine.hpp>



// Private Helper functions
bool Engine::tableExists(const string &name) {
  // filesystem::path path = "db/tables/" + name + ".meta";
  filesystem::path path = filesystem::path("db") / "tables" / (name + ".meta");
  return filesystem::exists(path);
}

bool Engine::openMetaFile(const string &name, fstream &file) {
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

bool Engine::writeMeta(const string &name, const vector<column> &columns,
               const column &primaryKey) {

  json j;
  j["table_name"] = name;

  for (auto &col : columns) {
    bool is_primary = (col.name == primaryKey.name);
    j["columns"].push_back({{"name", col.name},
                            {"type", col.type},
                            {"size", col.size},
                            {"is_indexed", is_primary ? true : col.isIndexed}});
  }

  j["primary_key"] = primaryKey.name;
  fstream file;
  if (!openMetaFile(name, file))
    return false;
  file << j.dump(4);
  file.close();
  return true;
}

bool Engine::createColumnFiles(const string &name, const vector<column> &columns) {
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

vector<ofstream> Engine::openColumnFiles(const string &tableName,
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



//Public functions
