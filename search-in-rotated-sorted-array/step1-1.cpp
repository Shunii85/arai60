#include <vector>
class Solution {
 public:
  int search(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
      int middle = left + (right - left) / 2;
      if (nums[middle] == target) {
        return middle;
      }
      if (nums[middle] < target) {
        if (nums[middle] <= nums[right] && target > nums[right]) {
          right = middle - 1;
          continue;
        }
        left = middle + 1;
      } else {
        if (nums[middle] > nums[right] && target <= nums[right]) {
          left = middle + 1;
          continue;
        }
        right = middle - 1;
      }
    }
    return -1;
  }
};
