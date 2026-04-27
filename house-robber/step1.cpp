#include <algorithm>
#include <vector>
class Solution {
 public:
  int rob(std::vector<int>& nums) {
    if (nums.size() == 0) {
      return 0;
    }
    int two_back_maximum = 0;
    int one_back_maximum = 0;
    int current = 0;
    for (int num : nums) {
      current = two_back_maximum + num;

      two_back_maximum = std::max(two_back_maximum, one_back_maximum);
      one_back_maximum = std::max(two_back_maximum, current);
    }
    return one_back_maximum;
  }
};
