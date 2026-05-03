#include <tuple>
#include <vector>
class Solution {
 public:
  int rob(const std::vector<int>& nums) {
    // each tuple contains
    // the first => maximum money, robbed there.
    // the second => maximum money, not robbed there.
    if (nums.empty()) {
      return 0;
    }
    std::tuple<int, int> first_house_robbed(nums[0], 0);
    std::tuple<int, int> first_house_not_robbed(0, 0);
    for (int place = 1; place < nums.size(); ++place) {
      const int money = nums[place];

      auto [max_robbed, max_not_robbed] = first_house_not_robbed;
      int robbed = max_not_robbed + money;
      int not_robbed = std::max(max_not_robbed, max_robbed);
      first_house_not_robbed = {robbed, not_robbed};

      if (place == nums.size() - 1) {
        continue;
      }
      auto [max_robbed_with_first, max_not_robbed_with_first] =
          first_house_robbed;
      robbed = max_not_robbed_with_first + money;
      not_robbed = std::max(max_not_robbed_with_first, max_robbed_with_first);
      first_house_robbed = {robbed, not_robbed};
    }
    // max candidates
    auto [max1, max2] = first_house_not_robbed;
    auto [max3, max4] = first_house_robbed;
    return std::max(std::max(max1, max2), std::max(max3, max4));
  }
};
