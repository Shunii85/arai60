#include <cassert>
#include <vector>
class Solution {
 public:
  int lengthOfLIS(const std::vector<int>& nums) {
    if (nums.empty()) {
      return 0;
    }
    std::vector<int> memo;
    for (int n : nums) {
      if (memo.empty() || memo.back() < n) {
        memo.push_back(n);
      } else {
        int bound = LowerBound(memo, n);
        memo[bound] = n;
      }
    }
    return memo.size();
  }

 private:
  int LowerBound(const std::vector<int>& nums, int n) {
    int range_start = 0;
    int range_end = nums.size() - 1;
    while (range_start <= range_end) {
      int range_mid = (range_start + range_end) / 2;
      int middle = nums[range_mid];
      if (middle == n) {
        return range_mid;
      }
      if (n < middle) {
        range_end = range_mid - 1;
      } else {
        range_start = range_mid + 1;
      }
    }
    return range_start;
  }
};
