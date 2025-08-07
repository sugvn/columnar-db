#include "column.hpp"
#include "engine.hpp"
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  vector<column> columns;
  string name, type;
  bool is_indexed;
  for (int i = 0; i < 3; i++) {
    cout << "Column " << i + 1 << ":\n";

    cout << "  Name: ";
    cin >> name;

    cout << "  Type: ";
    cin >> type;

    cout << "  Is Indexed (0 or 1): ";
    cin >> is_indexed;
    columns.push_back(column(name, type, is_indexed));
  }
  Engine db;
  if (!db.createTable("students", columns, columns[2])) {
    cout << "Failed to create Column files" << endl;
  }
db.loadColumns("students", columns);
  return 0;
}
