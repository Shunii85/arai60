#include <algorithm>
#include <vector>

using Grid = std::vector<std::vector<int>>;
enum {
  kWater = 0,
  kLand = 1,
  kVisited = -1,
};

class Solution {
 public:
  int maxAreaOfIsland(Grid grid) {
    if (grid.empty() || grid[0].empty()) {
      return 0;
    }
    int max_area = 0;
    int row_size = grid.size();
    int column_size = grid[0].size();
    for (int row = 0; row < row_size; ++row) {
      for (int column = 0; column < column_size; ++column) {
        if (grid[row][column] == kLand) {
          int area = CountIslandArea(grid, row, column);
          max_area = std::max(max_area, area);
        }
      }
    }
    return max_area;
  }

 private:
  int CountIslandArea(Grid& grid, int row, int column) {
    if (IsOutOfBounds(grid, row, column) || grid[row][column] != kLand) {
      return 0;
    }
    grid[row][column] = kVisited;
    int area_island = 1;
    area_island += CountIslandArea(grid, row + 1, column);
    area_island += CountIslandArea(grid, row - 1, column);
    area_island += CountIslandArea(grid, row, column + 1);
    area_island += CountIslandArea(grid, row, column - 1);
    return area_island;
  }
  bool IsOutOfBounds(const Grid& grid, int row, int column) {
    int row_size = grid.size();
    int column_size = grid[0].size();
    return !(0 <= row && row < row_size && 0 <= column && column < column_size);
  }
};
