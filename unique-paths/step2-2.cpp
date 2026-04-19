#include <vector>
class Cache {
 public:
  Cache(int row, int column)
      : pattern_cache_(row, std::vector<int>(column, -1)) {}
  int add(int row, int column, int num) {
    return pattern_cache_[row][column] = num;
  }
  int get(int row, int column) { return pattern_cache_[row][column]; }
  bool contains(int row, int column) { return get(row, column) != -1; }

 private:
  std::vector<std::vector<int>> pattern_cache_;
};

class Solution {
 public:
  int uniquePaths(int m, int n) {
    Cache cache(m, n);
    return paths(m - 1, n - 1, cache);
  }

 private:
  int paths(int row, int column, Cache& cache) {
    if (row == 0 || column == 0) {
      return cache.add(row, column, 1);
    }
    if (cache.contains(row, column)) {
      return cache.get(row, column);
    }
    return cache.add(
        row, column,
        paths(row - 1, column, cache) + paths(row, column - 1, cache));
  }
};
