#pragma once
#include "string"

struct Err {
        bool status;
        std::string msg;
        Err() : status(false), msg() {};
        Err(bool s, const std::string &m) : status(s), msg(m) {}
        explicit operator bool() const { return status; }
};

template <typename T> struct Res {
        T value;
        Err e;
        Res(T v) : value(v), e() {}
        Res(T v, const std::string &s) : value(v), e(true, s) {}
};
