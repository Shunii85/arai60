// とけなかった。
#include <limits>
#include <list>
#include <ranges>
#include <vector>
class Solution {
 public:
  int shipWithinDays(const std::vector<int>& weights, int days) {
    for (int i = 0; i < weights.size() - days; ++i) {
      int min_sum = std::numeric_limits<int>::max();
      int min_pair_index = 0;
      for (int package_i = 0; package_i < weights.size() - 1; ++i) {
        int sum = weights[package_i] + weights[package_i + 1];
        if (sum <= min_sum) {
          min_pair_index = package_i;
          min_sum = sum;
        }
      }
    }
  }
};
