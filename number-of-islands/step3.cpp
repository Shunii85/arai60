#include <vector>
using Grid = std::vector<std::vector<char>>;
class Solution {
 public:
  int numIslands(Grid grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    int num_islands = 0;
    int height = grid.size();
    int width = grid[0].size();
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        if (grid[y][x] == '1') {
          ++num_islands;
          visitIsland(grid, y, x);
        }
      }
    }
    return num_islands;
  }

 private:
  void visitIsland(Grid& grid, int y, int x) {
    if (isOutOfBounds(grid, y, x) || grid[y][x] != '1') {
      return;
    }
    grid[y][x] = '-';  // mark as visited with '-'
    visitIsland(grid, y + 1, x);
    visitIsland(grid, y - 1, x);
    visitIsland(grid, y, x + 1);
    visitIsland(grid, y, x - 1);
  }
  bool isOutOfBounds(const Grid& grid, int y, int x) {
    int height = grid.size();
    int width = grid[0].size();
    return !(0 <= x && x < width && 0 <= y && y < height);
  }
};