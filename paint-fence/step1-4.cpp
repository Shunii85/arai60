#include <cmath>
#include <queue>
#include <tuple>

enum PREVIOUS_TYPE { DUPLICATED, NON_DUPLICATED };
class Solution {
 public:
  int numWays(int n, int k) {
    if (n <= 2) {
      return std::pow(k, n);
    }
    std::queue<std::tuple<PREVIOUS_TYPE, int>> q;
    q.push({DUPLICATED, k});
    q.push({NON_DUPLICATED, k * (k - 1)});
    int nth = 2;
    while (nth < n) {
      int pattern_wide = q.size();
      int duplicate_pattern_num = 0;
      int non_duplicate_pattern_num = 0;
      for (int i = 0; i < pattern_wide; ++i) {
        auto [type, prev_pattern_num] = q.front();
        q.pop();
        if (type == DUPLICATED) {
          non_duplicate_pattern_num += prev_pattern_num * (k - 1);
        } else {
          duplicate_pattern_num += prev_pattern_num;
          non_duplicate_pattern_num += prev_pattern_num * (k - 1);
        }
      }
      q.push({DUPLICATED, duplicate_pattern_num});
      q.push({NON_DUPLICATED, non_duplicate_pattern_num});
      ++nth;
    }
    int num_ways = 0;
    while (!q.empty()) {
      auto [_, num] = q.front();
      q.pop();
      num_ways += num;
    }
    return num_ways;
  }
};
