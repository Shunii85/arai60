#include <tuple>
#include <vector>
class Solution {
 public:
  int rob(const std::vector<int>& nums) {
    if (nums.empty()) {
      return 0;
    }
    // each tuple contains
    // the first => maximum money, robbed there.
    // the second => maximum money, not robbed there.
    std::tuple<int, int> maybe_first_house_robbed(nums[0], 0);
    std::tuple<int, int> first_house_not_robbed(0, 0);
    for (int place = 1; place < nums.size(); ++place) {
      const int money = nums[place];
      updateMaximums(first_house_not_robbed, money);
      if (place == nums.size() - 1) {
        continue;
      }
      updateMaximums(maybe_first_house_robbed, money);
    }
    // max candidates
    auto [max1, max2] = first_house_not_robbed;
    auto [max3, max4] = maybe_first_house_robbed;
    return std::max(std::max(max1, max2), std::max(max3, max4));
  }

 private:
  void updateMaximums(std::tuple<int, int>& robbed_info, int money) {
    auto [robbed_maximum, not_robbed_maximum] = robbed_info;
    int robbed = not_robbed_maximum + money;
    int not_robbed = std::max(robbed_maximum, not_robbed_maximum);

    robbed_info = {robbed, not_robbed};
  }
};
