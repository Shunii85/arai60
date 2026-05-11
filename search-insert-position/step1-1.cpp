#include <vector>
class Solution {
 public:
  int searchInsert(const std::vector<int>& nums, int target) {
    int start = 0;
    int end = nums.size() - 1;
    while (start <= end) {
      int middle = (start + end) / 2;
      int num = nums[middle];
      if (num == target) {
        return middle;
      }
      if (num < target) {
        start = middle + 1;
      } else {
        end = middle - 1;
      }
    }
    return start;
  }
};
