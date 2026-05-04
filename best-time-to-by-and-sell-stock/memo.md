# step1

売るときのことだけ考えればよさそう。

- 売るときに、今までの一番安値で買えた値段を引けば、そのときの最大の利益が出る。
  - 最大の利益を更新していけばいい。今回は利益がマイナスになることを考慮してないから、初期値は0かな。
  - 最初の最も安値の値段はprices[0]かな。利益は1日目に利益が出るわけないから、0

  - [7,1,5,3,6,4]
  1. 7を最安値として、次に見ていく。
  2. 1 - 7 = -6. よって現状の最大利益0、最安値1
  3. 5 - 1 = 4. (max_profit, min_price) = (4, 1)
  4. 3 - 1 = 2. (4, 1)
  5. 6 - 1 = 5. (5, 1)
  6. 4 - 1 = 3. (5, 1)

  最大利益 5

- 書けた。

```cpp
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
```

# step2

- コメント集を呼んだ。pricesが空の時にどうするか。自分は0を返していたけど、確かにいろいろある。

- 特段帰るところもなかったのでstep2のコードは省く。

# step3

1. 2分2秒
2. 1分57秒
3. 1分34秒
