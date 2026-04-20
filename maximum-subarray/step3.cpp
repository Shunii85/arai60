#include <algorithm>
#include <limits>
#include <vector>
class Solution {
 public:
  int maxSubArray(const std::vector<int>& nums) {
    int max_sum = std::numeric_limits<int>::min();
    int prefix_sum = 0;
    int min_prefix_sum = 0;
    for (int num : nums) {
      prefix_sum += num;
      max_sum = std::max(max_sum, prefix_sum - min_prefix_sum);
      min_prefix_sum = std::min(min_prefix_sum, prefix_sum);
    }
    return max_sum;
  }
};
