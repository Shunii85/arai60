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
        continue;
      }
      int bound = LowerBound(memo, n);
      memo[bound] = n;
    }
    return memo.size();
  }

 private:
  int LowerBound(const std::vector<int>& nums, int n) {
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] >= n) {
        return i;
      }
    }
    return 0;
  }
};
