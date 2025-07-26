#pragma once
#include <string>
#include <iostream>
#include <system_error>
#include <vector>
#include <fstream>
#include <filesystem>
#include "column.hpp"
#include "json.hpp"
using json=nlohmann::json;
using namespace std;

class engine{
    private:

        bool tableExists(const string &name){
            filesystem::path path="db/tables/" + name + ".meta";
            return filesystem::exists(path);
        }

        bool writeMeta(const string &name,ofstream &file,const vector<column> &columns,const column &primaryKey){
            json j;
            j["table_name"] = name;

            for (auto &col : columns) {
                bool is_primary = (col.name == primaryKey.name);
                j["columns"].push_back({
                    {"name", col.name},
                    {"type", col.type},
                    {"size", col.size},
                    {"is_indexed", is_primary ? true : col.is_indexed}
                });
            }

            j["primary_key"] = primaryKey.name;

            if (!file.is_open()) return false;

            file << j.dump(4);
            file.close();
            return true;
        }

        bool createColumnFiles(const string &name,const vector<column> &columns){
            string path="db/data/" + name;
            error_code ec;
            filesystem::create_directory(path,ec);
            if(ec) return false;
            for (auto &col : columns) {
                string filePath = path + "/" + col.name + ".bin";
                std::ofstream file(filePath, std::ios::binary);
                if (!file.is_open()) return false;
                file.close();
            }
            return true;
        }

    public:

        bool createTable(const string &name,const vector<column> &columns,const column &primaryKey){
            if(tableExists(name)){
                cout<<"Table with the name "<<name<<" exists"<<endl;
                return false;
            }
            ofstream meta("db/tables/" + name+".meta");
            if(!meta.is_open()){
                cout<<"Failed to open file "<<name<<".meta";
                return false;
            }
            if(writeMeta(name,meta,columns,primaryKey)){
                return createColumnFiles(name,columns);
            }
            else{
                return false;
            }

        }
};
