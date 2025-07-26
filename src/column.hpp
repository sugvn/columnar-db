#pragma once
#include <string>
#include <unordered_map>
inline const std::unordered_map<std::string,int> typeSize={
    {"int",4},
    {"string",15},
    {"bool",1}
};

struct column{
    std::string name;
    std::string type;
    int size;
    bool is_indexed;
    column(std::string n,std::string t,bool i=false):name(n),type(t),size(typeSize.at(t)),is_indexed(i){}
    column()=default;
};
