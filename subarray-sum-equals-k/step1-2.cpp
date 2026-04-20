
#include <vector>
class Solution {
 public:
  int subarraySum(const std::vector<int>& nums, int k) {
    int count = 0;
    int sum = 0;
    for (int start = 0; start < nums.size(); ++start) {
      for (int end = start; end < nums.size(); ++end) {
        sum += nums[end];
        if (sum == k) count++;
      }
      sum = 0;
    }
    return count;
  }
};