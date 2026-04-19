#include <vector>
class Solution {
 public:
  int uniquePaths(int m, int n) {
    if (!(m > 0 && n > 0)) {
      return 0;
    }
    std::vector<std::vector<int>> pattern_grid(m, std::vector<int>(n, 0));
    for (int row = 0; row < m; ++row) {
      pattern_grid[row][0] = 1;
    }
    for (int column = 0; column < n; ++column) {
      pattern_grid[0][column] = 1;
    }

    for (int column = 1; column < n; ++column) {
      for (int row = 1; row < m; ++row) {
        pattern_grid[row][column] =
            pattern_grid[row][column - 1] + pattern_grid[row - 1][column];
      }
    }

    return pattern_grid[m - 1][n - 1];
  }
};
