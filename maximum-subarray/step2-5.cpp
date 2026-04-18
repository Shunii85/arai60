#include <algorithm>
#include <limits>
#include <vector>
class Solution {
 public:
  int maxSubArray(const std::vector<int>& nums) {
    if (nums.size() == 0) {
      return 0;
    }
    int elevation = 0;
    int max_difference = 0;
    for (int differnece : nums) {
      max_difference = std::max(max_difference, max_difference + differnece);
    }
    return max_difference;
  }
};
