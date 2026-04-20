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
        continue;
      }
      int bound = LowerBound(memo, n);
      assert(bound != -1);  // memo.back() >= n
      memo[bound] = n;
    }
    return memo.size();
  }

 private:
  // return -1 if any element in nums is smaller than n.
  int LowerBound(const std::vector<int>& nums, int n) {
    int finded_as_smaller = -1;
    int finded_as_larger = nums.size();
    while (finded_as_smaller + 1 < finded_as_larger) {
      int range_start = finded_as_smaller + 1;
      int range_end = finded_as_larger - 1;

      int middle_position = (range_start + range_end) / 2;
      int middle = nums[middle_position];
      if (middle == n) {
        return middle_position;
      }
      if (middle < n) {
        finded_as_smaller = middle_position;
      } else {
        finded_as_larger = middle_position;
      }
    }
    if (finded_as_larger == nums.size()) {
      return -1;
    }
    return finded_as_larger;
  }
};
