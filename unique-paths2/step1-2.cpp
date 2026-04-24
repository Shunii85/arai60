#include <vector>
class Solution {
 public:
  int uniquePathsWithObstacles(
      const std::vector<std::vector<int>>& obstacle_grid) {
    if (obstacle_grid.empty() || obstacle_grid[0].empty()
        || obstacle_grid[0][0]) {
      return 0;
    }
    int num_rows = obstacle_grid.size();
    int num_cols = obstacle_grid[0].size();
    std::vector<int> current_column(num_rows, 0);
    current_column[0] = 1;
    for (int col = 0; col < num_cols; ++col) {
      for (int row = 0; row < num_rows; ++row) {
        if (obstacle_grid[row][col]) {
          current_column[row] = 0;
          continue;
        }
        if (row == 0) {
          continue;
        }
        current_column[row] += current_column[row - 1];
      }
    }
    return current_column.back();
  }
};
