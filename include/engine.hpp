#pragma once

// Includes
#include "column.hpp"
#include <expected>
#include <string>
#include <vector>
using namespace std;

// Custom return types for easier error handling
template <typename T> using Res = std::expected<T, std::string>;
using Err = std::unexpected<std::string>;

class StorageEngine {
	public:
	Res<void> createTable(
		std::string name, const std::vector<Column> &columns);
    Res<void> InsertTable(std::string name,vector<std::string> values);
};
