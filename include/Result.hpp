#pragma once
#include "string"
using namespace std;

struct Err{
        bool status;
        string msg;
        Err():status(false),msg(){};
        Err(bool s,const string &m):status(s),msg(m){}
        explicit operator bool() const { return status; }
};

template<typename T>
struct Res{
        T value;
        Err e;
        Res(T v):value(v),e(){}
        Res(T v,const string &s):value(v),e(true,s){}
};
