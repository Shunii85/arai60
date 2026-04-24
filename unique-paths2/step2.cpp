#include <vector>
using Grid = std::vector<std::vector<int>>;
class Solution {
 public:
  int uniquePathsWithObstacles(const Grid& obstacle_grid) {
    if (obstacle_grid.empty() || obstacle_grid[0].empty()) {
      return 0;
    }
    if (obstacle_grid[0][0]) {
      return 0;
    }
    int num_rows = obstacle_grid.size();
    int num_cols = obstacle_grid[0].size();
    // pattern_grid[row][col] is the pattern to get to (row, col) place.
    Grid pattern_grid(num_rows, std::vector<int>(num_cols, 0));
    pattern_grid[0][0] = 1;
    for (int col = 0; col < num_cols; ++col) {
      for (int row = 0; row < num_rows; ++row) {
        CalculatePatterns(row, col, pattern_grid, obstacle_grid);
      }
    }
    return pattern_grid[num_rows - 1][num_cols - 1];
  }

 private:
  void CalculatePatterns(int row, int col, Grid& pattern_grid,
                         const Grid& obstacle_grid) {
    if (row == 0 && col == 0) {
      return;
    }
    if (obstacle_grid[row][col]) {
      pattern_grid[row][col] = 0;
      return;
    }
    int here_pattern = 0;
    if (row > 0) {
      here_pattern += pattern_grid[row - 1][col];
    }
    if (col > 0) {
      here_pattern += pattern_grid[row][col - 1];
    }
    pattern_grid[row][col] = here_pattern;
  }
};
