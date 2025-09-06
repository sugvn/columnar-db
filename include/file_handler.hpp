#pragma once
#include <Result.hpp>
#include <algorithm>
#include <expected>
#include <fstream>
#include <ios>
#include <string>

enum fileType { META, COL };

class fileHandler {
      public:
        Res<std::fstream> openFile(std::string name, fileType ft) {
                std::fstream file;
                if (ft == fileType::META) {
                        name += ".meta";
                        // opening here to decide whether to open as binary or not
                        file.open(name, std::ios::in | std::ios::out);
                } else if (ft == fileType::COL) {
                        name += ".col";
                        // opening here to decide whether to open as binary or not
                        file.open(name, std::ios::in | std::ios::out | std::ios::binary);
                } else {
                        return Err("Invalid filetype");
                }
                return std::move(file);
        }
};
