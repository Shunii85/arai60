#include <vector>
class Solution {
 public:
  int searchInsert(const std::vector<int>& nums, int target) {
    int start = 0;
    int found_same_or_larger = nums.size();
    while (start < found_same_or_larger) {
      int end = found_same_or_larger - 1;
      int middle = (start + end) / 2;
      int num = nums[middle];
      if (num < target) {
        start = middle + 1;
      } else {
        found_same_or_larger = middle;
      }
    }
    return found_same_or_larger;
  }
};
