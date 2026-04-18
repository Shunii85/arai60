#include <algorithm>
#include <limits>
#include <vector>
class Solution {
 public:
  int maxSubArray(const std::vector<int>& nums) {
    if (nums.size() == 0) {
      return 0;
    }
    // includes each largest sums
    std::vector<int> gaps(nums.size());
    int elevation = 0;
    int lowest_elevation = 0;
    for (int i = 0; i < nums.size(); ++i) {
      elevation += nums[i];
      if (elevation < lowest_elevation) {
        lowest_elevation = elevation;
        gaps[i] = nums[i];
        continue;
      }
      gaps[i] = elevation - lowest_elevation;
    }
    return *std::max_element(gaps.begin(), gaps.end());
  }
};
