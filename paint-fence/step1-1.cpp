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
      for (int i = 0; i < pattern_wide; ++i) {
        auto [type, prev_pattern_num] = q.front();
        q.pop();
        if (type == DUPLICATED) {
          q.push({NON_DUPLICATED, prev_pattern_num * (k - 1)});
        } else {
          q.push({DUPLICATED, prev_pattern_num});
          q.push({NON_DUPLICATED, prev_pattern_num * (k - 1)});
        }
      }
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
