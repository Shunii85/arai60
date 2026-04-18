#include <algorithm>
#include <limits>
#include <vector>
class Solution {
 public:
  int maxSubArray(const std::vector<int>& nums) {
    int max_sum = std::numeric_limits<int>::min();
    for (int i = 0; i < nums.size(); ++i) {
      int subarray_sum = nums[i];
      max_sum = std::max(max_sum, subarray_sum);
      for (int j = i + 1; j < nums.size(); ++j) {
        subarray_sum += nums[j];
        max_sum = std::max(max_sum, subarray_sum);
      }
    }
    return max_sum;
  }
};
