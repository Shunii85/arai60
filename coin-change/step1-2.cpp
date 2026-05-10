#include <unordered_set>
#include <vector>
class Solution {
 public:
  int coinChange(const std::vector<int>& coins, int target_amount) {
    std::vector<int> valid_coins;
    for (int coin : coins) {
      if (coin > target_amount) {
        continue;
      }
      valid_coins.push_back(coin);
    }

    int num_coins = 0;
    // each amount in `amounts` can be made by current `num_coins`.
    // 0 can be made by 0 coins.
    std::vector<int> amounts({0});
    std::unordered_set<int> made;
    while (!amounts.empty()) {
      std::vector<int> next_amounts;
      for (int amount : amounts) {
        if (amount == target_amount) {
          return num_coins;
        }
        for (int coin_kind : valid_coins) {
          int new_amount = amount + coin_kind;
          if (made.contains(new_amount)) {
            continue;
          }
          if (new_amount > target_amount) {
            continue;
          }
          next_amounts.push_back(new_amount);
          made.insert(new_amount);
        }
      }
      amounts = std::move(next_amounts);
      num_coins++;
    }

    return -1;  // cannot be made up.
  }
};
