#include <vector>
class Solution {
 public:
  int uniquePaths(int m, int n) {
    std::vector<int> current_column(m, 0);
    current_column[0] = 1;
    for (int _column = 0; _column < n; ++_column) {
      for (int row = 1; row < m; ++row) {
        current_column[row] += current_column[row - 1];
      }
    }
    return current_column.back();
  }
};
