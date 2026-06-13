#include <vector>
class Solution {
 public:
  int search(const std::vector<int>& nums, int target) {
    int offset = FindMinIndex(nums);
    int virtual_left = 0;
    int virtual_right = nums.size() - 1;
    while (virtual_left <= virtual_right) {
      int virtual_middle = virtual_left + (virtual_right - virtual_left) / 2;
      int middle = (virtual_middle + offset) % nums.size();
      if (nums[middle] == target) {
        return middle;
      }
      if (nums[middle] < target) {
        virtual_left = virtual_middle + 1;
      } else {
        virtual_right = virtual_middle - 1;
      }
    }
    return -1;
  }

 private:
  int FindMinIndex(const std::vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    while (left < right) {
      int middle = left + (right - left) / 2;
      if (nums[middle] <= nums[right]) {
        right = middle;
      } else {
        left = middle + 1;
      }
    }
    return left;
  }
};
