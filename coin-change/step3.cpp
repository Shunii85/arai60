#include <limits>
#include <vector>
class Solution {
 public:
  int coinChange(const std::vector<int>& coins, int amount) {
    std::vector<int> min_num_coins(amount + 1, std::numeric_limits<int>::max());
    min_num_coins[0] = 0;
    std::vector<int> made(amount + 1, false);
    made[0] = true;
    for (int money = 0; money < amount; ++money) {
      if (!made[money]) {
        continue;
      }
      const int num_coins = min_num_coins[money];
      for (int coin_kind : coins) {
        if (coin_kind > amount) {
          continue;
        }
        int added_one_coin = money + coin_kind;
        if (added_one_coin <= amount) {
          min_num_coins[added_one_coin] =
              std::min(min_num_coins[added_one_coin], num_coins + 1);
          made[added_one_coin] = true;
        }
      }
    }
    return made[amount] ? min_num_coins[amount] : -1;
  }
};
