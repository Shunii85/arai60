#include <algorithm>
#include <vector>
class Solution {
 public:
  int rob(std::vector<int>& nums) {
    if (nums.size() == 0) {
      return 0;
    }
    int non_robbed_maximum = 0;
    int maximum = 0;
    for (int money : nums) {
      int robbed = non_robbed_maximum + money;

      non_robbed_maximum = maximum;
      maximum = std::max(maximum, robbed);
    }
    return maximum;
  }
};
