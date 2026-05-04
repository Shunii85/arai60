#include <limits>
#include <vector>
class Solution {
 public:
  int maxProfit(std::vector<int> prices) {
    if (prices.empty()) {
      return 0;
    }
    int max_profit = 0;
    int buy_price = 0;
    int sell_price = 0;
    int last_day_price = std::numeric_limits<int>::max();
    prices.push_back(-1);  // dummy for calc the last profit.
    for (int price : prices) {
      if (price >= last_day_price) {
        sell_price = price;
        last_day_price = price;
        continue;
      }
      max_profit += sell_price - buy_price;
      buy_price = sell_price = last_day_price = price;
    }
    return max_profit;
  }
};
