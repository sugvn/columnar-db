#pragma once
#include <algorithm>
#include <expected>
#include <filesystem>
#include <fstream>
#include <ios>
#include <memory>
#include <string>

// Custom return types for easier error handling
template <typename T> using Res = std::expected<T, std::string>;
using Err = std::unexpected<std::string>;

class fileHandler {
      public:
        Res<void> createMetaFile(const std::string& name) {
                std::filesystem::path path = std::filesystem::path("data") / "tables" / (name + ".meta");
                if(std::filesystem::exists(path)){
                        return Err("File already exists");
                }
                std::fstream file=std::fstream(path,std::ios::out);
                if(!file.is_open()){
                        return Err("Error opening file");
                }
                file.close();
                return {};
        }

        Res<std::unique_ptr<std::fstream>> openMetaFile(const std::string& name) {
                std::filesystem::path path = std::filesystem::path("data") / "tables" / (name + ".meta");
                if(!std::filesystem::exists(path)){
                        return Err("File does not exists");
                }
                auto file = std::make_unique<std::fstream>(path,std::ios::in | std::ios::out);
                if(!file->is_open()){
                        return Err("Cannot open file");
                }
                return file;
        }
};
