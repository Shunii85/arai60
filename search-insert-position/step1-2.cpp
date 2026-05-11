#include <vector>
class Solution {
 public:
  int searchInsert(const std::vector<int>& nums, int target) {
    int found_smaller_pos = -1;
    int found_larger_pos = nums.size();
    while (found_smaller_pos + 1 < found_larger_pos) {
      int start = found_smaller_pos + 1;
      int end = found_larger_pos - 1;
      int middle = (start + end) / 2;
      int num = nums[middle];
      if (num == target) {
        return middle;
      }
      if (num < target) {
        found_smaller_pos = middle;
      } else {
        found_larger_pos = middle;
      }
    }
    return found_smaller_pos + 1;
  }
};
