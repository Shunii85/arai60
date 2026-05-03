// 解けていない
#include <algorithm>
#include <tuple>
#include <vector>
class Solution {
 public:
  int rob(const std::vector<int>& nums) {
    if (nums.empty()) {
      return 0;
    }
    if (nums.size() == 1) {
      return nums[0];
    }
    if (nums.size() == 2) {
      return std::max(nums[0], nums[1]);
    }
    // The first is max total money robbed until the place.
    // The second is if robbed the first house.
    std::vector<std::tuple<int, bool>> maximum_moneys;
    maximum_moneys.reserve(nums.size());
    maximum_moneys[0] = {nums[0], true};
    maximum_moneys[1] = {nums[1], false};
    for (int place = 2; place < nums.size(); ++place) {
      auto [robbed_maximum_without_neighbor, from_first1] =
          maximum_moneys[place - 2];
      auto [maximum_by_neighbor, from_first2] = maximum_moneys[place - 1];
      if (place == nums.size() - 1) {
        if (!from_first1) {
          maximum_moneys[maximum_by_neighbor];
        }
        continue;
      }
      auto [robbed_maximum_without_neighbor, from_first1] =
          maximum_moneys[place - 2];
      auto [maximum_by_neighbor, from_first2] = maximum_moneys[place - 1];
      int robbed_here = robbed_maximum_without_neighbor + nums[place];
      if (robbed_here > maximum_by_neighbor) {
        maximum_moneys[place] = {robbed_here, from_first1};
        continue;
      }
      if (robbed_here < maximum_by_neighbor) {
        maximum_moneys[place] = {maximum_by_neighbor, from_first2};
        continue;
      }

      if (from_first1) {
        maximum_moneys[place] = maximum_moneys[place - 2];
      }
      maximum_moneys[place] = maximum_moneys[place - 1];
    }
    std::max_element(maximum_moneys.begin(), maximum_moneys.end());
  }
};
