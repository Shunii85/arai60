#include <vector>
class Solution {
 public:
  int uniquePaths(int num_rows, int num_columns) {
    std::vector<int> current_column(num_rows);
    current_column[0] = 1;
    for (int _column = 0; _column < num_columns; ++_column) {
      for (int row = 1; row < num_rows; ++row) {
        current_column[row] += current_column[row - 1];
      }
    }
    return current_column.back();
  }
};