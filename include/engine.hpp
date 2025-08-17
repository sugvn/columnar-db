#pragma once
#include "Result.hpp"
#include "column.hpp"
#include <fstream>
#include <string>
#include <variant>
#include <vector>
using std::string;
using std::vector;
using None = std::monostate;

class Engine {

      private:
        // general helper
        bool tableExists(const string &name); // done

        // MetaFile utilities
        Res<None> createMetaFile(const string &name);  // done
        Res<fstream> openMetaFile(const string &name); // done
        Res<None> writeMeta(const string &name, const vector<Column> &columns);

        // Column(.col) files utilities
        Res<None> createColumnFiles(const string &name,
                                    const vector<Column> &columns);
        Res<vector<fstream>> openColumnFiles(const string &tableName,
                                             const vector<Column> &cols);

        // idk what to do with this
        bool loadColumns(const string &name, vector<Column> &columns);

      public:
        bool createTable(const string &name, const vector<Column> &columns,
                         const Column &primaryKey);
        bool insertIntoTable(const string &name, const vector<string> &vec);
};
