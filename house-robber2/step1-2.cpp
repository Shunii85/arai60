#include <vector>
class Solution {
 public:
  int rob(const std::vector<int>& nums) {
    if (nums.empty()) {
      return 0;
    }
    if (nums.size() == 1) {
      return nums[0];
    }
    return std::max(robHelper(nums, 0, nums.size() - 1),
                    robHelper(nums, 1, nums.size()));
  }

 private:
  int robHelper(const std::vector<int>& nums, int from, int to) {
    int maximum_not_robbed_neighbor = 0;
    int maximum = 0;
    for (int place = from; place < to; ++place) {
      int robbed_here = maximum_not_robbed_neighbor + nums[place];

      maximum_not_robbed_neighbor = maximum;
      maximum = std::max(maximum, robbed_here);
    }
    return maximum;
  }
};
