#include <cassert>
#include <vector>
class Solution {
 public:
  int findMin(const std::vector<int>& nums) {
    assert(!nums.empty());
    int left = 0;
    int right = nums.size();
    while (left < right) {
      int middle = left + (right - left) / 2;
      if (nums[middle] <= nums.back()) {
        right = middle;
      } else {
        left = middle + 1;
      }
    }
    return nums[left];
  }
};
