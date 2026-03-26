#include <vector>
class Solution {
 public:
  int subarraySum(const std::vector<int>& nums, int k) {
    int subarray_head = 0;
    int checking_pos = 0;
    int sum = 0;
    int count = 0;
    while (subarray_head < nums.size()) {
      if (checking_pos == nums.size()) {
        sum = 0;
        checking_pos = ++subarray_head;
        continue;
      }
      sum += nums[checking_pos++];
      if (sum == k) ++count;
    }
    return count;
  }
};