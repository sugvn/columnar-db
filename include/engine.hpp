
#pragma once

//Includes
#include <string>
#include <vector>
#include "column.hpp"
#include <expected>

//Custom return types for easier error handling
template <typename T>
using Res=std::expected<T,std::string>;
using Err=std::unexpected<std::string>;

class StorageEngine {
      public:
        Res<void> createTable(std::string name, const std::vector<Column> &columns);
};
