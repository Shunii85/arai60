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
    int lowest_elevation = 0;
    int max_difference = std::numeric_limits<int>::min();
    for (int differnece : nums) {
      elevation += differnece;
      if (elevation < lowest_elevation) {
        max_difference = std::max(max_difference, elevation - lowest_elevation);
        lowest_elevation = elevation;
        continue;
      }
      max_difference = std::max(max_difference, elevation - lowest_elevation);
    }
    return max_difference;
  }
};
