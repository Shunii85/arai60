#include <vector>
class Solution {
 public:
  int searchInsert(const std::vector<int>& nums, int target) {
    int start = 0;
    int ended = nums.size();
    while (start < ended) {
      int end = ended - 1;
      int middle = (start + end) / 2;
      int num = nums[middle];
      if (num < target) {
        start = middle + 1;
      } else {
        ended = middle;
      }
    }
    return ended;  // または、start
  }
};
