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

        vector<ofstream> openColumnFiles(const string &tableName,const vector<column> &columns){
            vector<ofstream> files;
            for(const auto &col:columns){
                ofstream file("db/data/" + tableName + "/" + col.name + ".bin");
                if(!file.is_open()){
                    cout<<"Error opening column file"<<endl;
                    return {};
                }
                files.push_back(file);
            }
            return files;

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
        
       bool insertIntoTable(const string &name,const vector<string> &vec){
        if(!tableExists(name)){
            cout<<"Table does not exist";
            return false;
        } 
        ifstream file("db/tables" + name + ".meta");
        json j;
        if(!file.is_open()){
            cout<<"Error opening file for inserting";
            return false;
        }
        file>>j;
        vector<column> columns;
        for(const auto& col:j["columns"]){
            columns.push_back(column(col["name"],col["type"],col["is_indexed"]));
        }
        const vector<ofstream> &files=openColumnFiles(name,columns);
        if(!files.size()){
            return false;
        }
    } 
};
