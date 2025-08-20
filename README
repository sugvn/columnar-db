
# Project Scope: In‑Memory Columnar Database Engine

This document defines the scope, features, and constraints of the in‑memory columnar database engine project. The design is intentionally minimal, optimized for analytical workloads rather than transactional workloads.

---

## 1. Storage Model

* **Primary Storage:**

  * Data is stored in **columnar format** in memory for fast analytical queries.
  * Each column is represented as a contiguous memory block (e.g., `std::vector<T>` in C++).

* **Disk Persistence:**

  * Periodic **snapshots** are saved to disk for durability.
  * Snapshots may be serialized to a binary format or compressed CSV.

```cpp
// Example: Column representation
struct Column {
    std::string name;
    std::string type; // e.g., "int", "float", "string"
    std::vector<std::string> data;
};
```

---

## 2. Data Ingestion

* **Batch Inserts Only:**

  * Rows are collected into temporary CSV files.
  * When a threshold (e.g., 1M rows) is reached, the batch is loaded into memory.

* **Compression (Optional):**

  * Dictionary encoding for string columns.
  * Goal: reduce memory footprint for large datasets.

```cpp
// Example: Dictionary encoding
class DictionaryEncodedColumn {
    std::unordered_map<std::string, int> dictionary;
    std::vector<int> encoded;
};
```

---

## 3. Query Model

* **Read‑Only Queries:**

  * No support for `DELETE` or `UPDATE`.
  * Queries are strictly **aggregations** and scans.

* **Supported Operations:**

  * `SUM`, `COUNT`, `AVG`, `MIN`, `MAX`.
  * Column filtering with simple predicates (e.g., `WHERE col > 100`).

```cpp
// Example: SUM aggregation
long sum(const std::vector<int>& col) {
    long total = 0;
    for (int val : col) total += val;
    return total;
}
```

---

## 4. Caching & Memory Management

* **In‑Memory First:**

  * Keep as much data as possible in memory.

* **Fallback Strategy:**

  * If memory is insufficient, implement a small **LRU cache** for columns.
  * Least recently used columns are evicted to disk.

```cpp
// Pseudocode: LRU cache for column blocks
class LRUCache {
    std::list<std::string> order;
    std::unordered_map<std::string, std::vector<int>> cache;
    size_t capacity;
};
```

---

## 5. Disk Persistence

* **Snapshots:**

  * Entire database state can be written to disk.
  * Useful for crash recovery or cold restarts.

* **No WAL / Journaling:**

  * Simplicity prioritized over strict durability guarantees.

```cpp
// Example: Writing snapshot
void saveSnapshot(const std::vector<Column>& table, const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);
    for (auto& col : table) {
        for (auto& val : col.data) out << val << ",";
        out << "\n";
    }
}
```

---

## 6. Parallelism (Optional / Future)

* Some operations (e.g., aggregations) may be parallelized.
* Use **multithreading** for large datasets.

```cpp
// Example: Parallel sum using threads
long parallel_sum(const std::vector<int>& col) {
    size_t mid = col.size() / 2;
    long left = 0, right = 0;
    std::thread t1([&](){ for (size_t i=0; i<mid; i++) left += col[i]; });
    std::thread t2([&](){ for (size_t i=mid; i<col.size(); i++) right += col[i]; });
    t1.join();
    t2.join();
    return left + right;
}
```

---

## 7. Out of Scope

* **No Deletes:**

  * Once inserted, data is immutable.
* **No Updates:**

  * Simplifies storage model and query execution.
* **No Transactional Guarantees (ACID):**

  * Not intended for OLTP.

---

## 8. Target Use Cases

* Analytical queries on large, mostly append‑only datasets.
* Scenarios with millions/billions of rows where **speed of aggregation** is more important than row‑level updates.
* Learning and demonstrating columnar storage design and query execution principles.

---

## 9. Possible Extensions

* More advanced compression (RLE, delta encoding).
* Column indexing (e.g., bitmap indexes).
* Vectorized execution for queries.
* Support for SQL‑like query parsing.

---

### Note
The code snippets in this document are provided for **conceptual clarity** and to illustrate the design philosophy of the project.  
They should not be interpreted as complete or production-ready implementations.  
The finalized source code within the repository may differ in structure, optimization, and detail to ensure robustness and efficiency.

