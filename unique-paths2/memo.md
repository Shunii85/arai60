# step1

- unique pathsの障害物があるバージョン

- 二次元配列の解法すこし躓いたのは、
  - 最初の行と列。ここ埋めてからでないと始まらないけど、一度障害物にぶつかったらその先へは進めないので、それ以降パターンは0

```cpp
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

```

- 1次元配列のがすっきりかけそう。
- こっちはこっちで微妙

```cpp
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

```

# step2

step1-1.cppがもっとわかりやすく書けそうだったので書き直す。

- 一番しっくり来た
- ただ、(0, 0)が1である前提。それは最初に省いている。
  - これ、条件ブロックわざわざ分けなくてよかったかな？条件繋がりすぎるとわかりにくいと感じたから。

```cpp
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
```

# step3

1. 6分04秒
2. 5分44秒
3. 5分40秒
