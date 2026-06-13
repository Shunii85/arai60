#include <vector>
class Solution {
 public:
  int search(const std::vector<int>& nums, int target) {
    int min_index = findMinIndex(nums);
    if (0 < min_index && nums[0] <= target && target <= nums[min_index - 1]) {
      return binarySearch(nums, 0, min_index - 1, target);
    }
    if (min_index <= nums.size() - 1 && nums[min_index] <= target
        && target <= nums.back()) {
      return binarySearch(nums, min_index, nums.size() - 1, target);
    }
    return -1;
  }

 private:
  int findMinIndex(const std::vector<int>& nums) {
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
    return left;
  };

  int binarySearch(const std::vector<int>& nums, int left, int right,
                   int target) {
    while (left <= right) {
      int middle = left + (right - left) / 2;
      if (nums[middle] == target) {
        return middle;
      }
      if (nums[middle] < target) {
        left = middle + 1;
      } else {
        right = middle - 1;
      }
    }
    return -1;
  };
};
