#pragma once
#include <string>
#include <vector>
#include "column.hpp"

class StorageEngine {
      public:
        void createTable(std::string name, const std::vector<Column> &columns);
};
