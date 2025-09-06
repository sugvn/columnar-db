#pragma once
#include <algorithm>
#include <expected>
#include <filesystem>
#include <fstream>
#include <ios>
#include <string>

// Custom return types for easier error handling
template <typename T> using Res = std::expected<T, std::string>;
using Err = std::unexpected<std::string>;

class fileHandler {
      public:
        Res<void> createFile(std::filesystem::path path) {
                if(std::filesystem::exists(path)){
                        return Err("File already exists");
                }
                std::fstream file=std::fstream(path,std::ios::in | std::ios::out);
                if(!file.is_open()){
                        return Err("Error opening file");
                }
                file.close();
                return {};
        }

        Res<std::fstream> openMetaFile(std::filesystem::path path) {
                std::fstream file;
                file.open(path, std::ios::in | std::ios::out | std::ios::app);
                if(!file.is_open()){
                        return Err("Cannot open file");
                }
                return std::move(file);
        }
};
