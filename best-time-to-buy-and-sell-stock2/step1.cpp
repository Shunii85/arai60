#include <limits>
#include <vector>
class Solution {
 public:
  int maxProfit(std::vector<int> prices) {
    if (prices.empty()) {
      return 0;
    }
    int max_profit = 0;
    int buy_price = prices[0];
    int sell_price = prices[0];
    int last_day_price = prices[0];
    prices.push_back(std::numeric_limits<int>::min());
    for (int i = 1; i < prices.size(); ++i) {
      const int price = prices[i];
      if (price >= last_day_price) {
        sell_price = price;
        last_day_price = price;
        continue;
      }
      max_profit += sell_price - buy_price;
      buy_price = sell_price = last_day_price = price;
    }
    max_profit += sell_price - buy_price;
    return max_profit;
  }
};
