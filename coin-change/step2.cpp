#include <algorithm>
#include <limits>
#include <vector>
class Solution {
 public:
  int coinChange(const std::vector<int>& coins, int amount) {
    // min_coin_nums[amount] is the minimum number of coins which can made up
    // amount.
    std::vector<int> min_coin_nums(amount + 1, std::numeric_limits<int>::max());
    std::vector<int> calculated(amount + 1, false);
    min_coin_nums[0] = 0;  // 0 can be made up without using any coins.
    calculated[0] = true;
    for (int money = 0; money < amount; ++money) {
      if (!calculated[money]) {
        continue;
      }
      const int num_coins = min_coin_nums[money];
      for (int coin_kind : coins) {
        if (coin_kind > amount) {
          continue;
        }
        int added_one_coin = money + coin_kind;
        if (added_one_coin <= amount) {
          min_coin_nums[added_one_coin] =
              std::min(min_coin_nums[added_one_coin], num_coins + 1);
          calculated[added_one_coin] = true;
        }
      }
    }
    return calculated[amount] ? min_coin_nums[amount] : -1;
  }
};
