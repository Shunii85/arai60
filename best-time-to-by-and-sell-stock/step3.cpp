#include <algorithm>
#include <vector>
class Solution {
 public:
  int maxProfit(const std::vector<int>& prices) {
    if (prices.empty()) {
      return 0;
    }
    int max_profit = 0;
    int min_price = prices[0];
    for (int i = 1; i < prices.size(); ++i) {
      int price = prices[i];
      max_profit = std::max(max_profit, price - min_price);
      min_price = std::min(min_price, price);
    }
    return max_profit;
  }
};
