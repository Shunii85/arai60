#include <tuple>
#include <vector>
class Solution {
 public:
  int rob(const std::vector<int>& nums) {
    // each tuple has
    // the first => maximum money, robbed there
    // the second => maximum money, not robbed there
    std::tuple<int, int> maybe_first_robbed(nums[0], 0);
    std::tuple<int, int> not_first_robbed(0, 0);
    for (int place = 1; place < nums.size(); ++place) {
      const int money = nums[place];
      updateMaximums(not_first_robbed, money);
      if (place != nums.size() - 1) {
        updateMaximums(maybe_first_robbed, money);
      }
    }
    auto [max1, max2] = maybe_first_robbed;
    auto [max3, max4] = not_first_robbed;
    return std::max(std::max(max1, max2), std::max(max3, max4));
  }

 private:
  void updateMaximums(std::tuple<int, int>& robbed_info, int money) {
    auto [robbed_max, not_robbed_max] = robbed_info;
    int robbed = not_robbed_max + money;
    int not_robbed = std::max(robbed_max, not_robbed_max);

    robbed_info = {robbed, not_robbed};
  }
};