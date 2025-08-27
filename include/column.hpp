#pragma once
#include <string>

//type ColumnType to represent the datatype a column holds in memory
//contains INT,STRING,BOOL initially
//maybe extended......maybee

enum ColumnType { INT, STRING, BOOL };

//class Column that represents a column of a table in memory
//The constructor takes a tableName:string,name:string,type:ColumnType
//The passing of ColumnType and not a string(eg:"int","bool","string") as a parameter to the constructor is deliberate
//the conversion of string to ColumnType will be handled at a higher level
//i.e Seperation of Concerns

class Column {
      private:
        std::string tableName;
        std::string name;
        ColumnType type;

      public:
        Column() = default;
        Column(const std::string &tableName, const std::string &name,
               ColumnType type)
            : tableName(tableName), name(name), type(type) {}
};
