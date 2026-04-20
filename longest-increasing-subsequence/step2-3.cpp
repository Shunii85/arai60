#include <algorithm>
#include <vector>
class Solution {
 public:
  int lengthOfLIS(const std::vector<int>& nums) {
    std::vector<int> memo;
    for (auto n : nums) {
      if (memo.empty() || memo.back() < n) {
        memo.push_back(n);
        continue;
      }
      auto bound_itr = std::lower_bound(memo.begin(), memo.end(), n);
      if (bound_itr == memo.end()) {
        continue;
      }
      *bound_itr = n;
    }
    return memo.size();
  }
};
