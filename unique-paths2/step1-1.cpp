#include <vector>
using Grid = std::vector<std::vector<int>>;
class Solution {
 public:
  int uniquePathsWithObstacles(const Grid& obstacle_grid) {
    if (obstacle_grid.empty() || obstacle_grid[0].empty()) {
      return 0;
    }
    int num_rows = obstacle_grid.size();
    int num_cols = obstacle_grid[0].size();
    Grid pattern_grid(num_rows, std::vector<int>(num_cols, 0));
    for (int col = 0; col < num_cols; ++col) {
      if (obstacle_grid[0][col]) {
        break;
      }
      pattern_grid[0][col] = 1;
    }
    for (int row = 0; row < num_rows; ++row) {
      if (obstacle_grid[row][0]) {
        break;
      }
      pattern_grid[row][0] = 1;
    }

    for (int col = 1; col < num_cols; ++col) {
      for (int row = 1; row < num_rows; ++row) {
        CalcPattern(row, col, pattern_grid, obstacle_grid);
      }
    }

    return pattern_grid[num_rows - 1][num_cols - 1];
  }

 private:
  void CalcPattern(int row, int col, Grid& pattern_grid,
                   const Grid& obstacle_grid) {
    if (obstacle_grid[row][col]) {
      return;
    }
    pattern_grid[row][col] =
        pattern_grid[row - 1][col] + pattern_grid[row][col - 1];
  }
};
