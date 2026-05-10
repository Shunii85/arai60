#include <algorithm>
#include <cstdint>
#include <limits>
#include <unordered_map>
#include <vector>
class Solution {
 public:
  int coinChange(const std::vector<int>& coins, int amount) {
    std::vector<int64_t> coin_nums(amount + 1, -1);
    coin_nums[0] = 0;  // 0 can be made up without using any coins.
    for (int64_t money = 0; money <= amount; ++money) {
      const int64_t num_coins = coin_nums[money];
      if (num_coins == -1) {
        continue;
      }
      for (int coin_kind : coins) {
        int64_t added_one_coin = money + coin_kind;
        if (added_one_coin <= amount) {
          if (coin_nums[added_one_coin] == -1) {
            coin_nums[added_one_coin] = std::numeric_limits<int>::max();
          }
          coin_nums[added_one_coin] =
              std::min(coin_nums[added_one_coin], num_coins + 1);
        }
      }
    }
    return coin_nums.back();
  }
};
