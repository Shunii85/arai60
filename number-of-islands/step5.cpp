#include <queue>
#include <vector>
using Grid = std::vector<std::vector<char>>;
using Candidates = std::queue<std::pair<int, int>>;
class Solution {
 public:
  int numIslands(Grid grid) {
    if (grid.empty() || grid[0].empty()) {
      return 0;
    }
    int num_island = 0;
    int row_size = grid.size();
    int column_size = grid[0].size();
    for (int row = 0; row < row_size; ++row) {
      for (int column = 0; column < column_size; ++column) {
        if (grid[row][column] == '1') {
          ++num_island;
          VisitIsland(grid, row, column);
        }
      }
    }
    return num_island;
  }

 private:
  void VisitIsland(Grid& grid, int row, int column) {
    Candidates next_lands;
    next_lands.push({row, column});
    while (!next_lands.empty()) {
      auto [row, column] = next_lands.front();
      next_lands.pop();

      AddNextLand(next_lands, grid, row + 1, column);
      AddNextLand(next_lands, grid, row - 1, column);
      AddNextLand(next_lands, grid, row, column + 1);
      AddNextLand(next_lands, grid, row, column - 1);
    }
  }
  void AddNextLand(Candidates& candidates, Grid& grid, int row, int column) {
    if (IsOutOfBounds(grid, row, column) || grid[row][column] != '1') {
      return;
    }
    grid[row][column] = '-';  // mark as visited with '-'
    candidates.push({row, column});
  }
  bool IsOutOfBounds(const Grid& grid, int row, int column) {
    int row_size = grid.size();
    int column_size = grid[0].size();
    return !(0 <= row && row < row_size && 0 <= column && column < column_size);
  }
};