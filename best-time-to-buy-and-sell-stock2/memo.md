# step1

- 今回は、売買が、同じ日に複数回できるらしい。ただし、いつでも保有できる株の数は最大1まで。

- 途中で売って、買い直して別日に売るほうが利益が高いことがある。
  - 普通に考えて、下がったときに買ったほうがいいよね。
    - 紆余曲折あって、価格が下がってしまってから上がったとしても、予測できるなら道中下がったところで買って、上がり幅を最大にしたい。つまり、チャートがわかっていれば、右肩上がりになる最初で買って下がる前に売るのがベスト。
  1. 最初の購入価格はprices[0]にしておいて、値段が前回と比べて上がっている場合は売り値を更新していく。
  2. 値段が下がったときに、
    - 手元の記録にある、売値 - 買値をする。
    - 買値を今の株の値段にする。
  
- 最初間違えた。
  - 最後が前日よりも上がっていたら、その買値は精算されないことになる。
  - ダミーとして、-∞(intの範囲の)の値段を追加した。

```cpp
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

    // 後から思ったけど、-1でも価格としてはおかしいから、意図も伝わるし動く。
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
    return max_profit;
  }
};
```

- 最後の取引も精算すればいいので、forの後に

  ```cpp
  max_profit += sell_price - buy_price;
  ```
  
  と書くだけでもいい。

- でも、最初から値段としてはありえないものを最後に追加していたら、意図を伝えやすいかもしれない。
  - どういうための値、ダミーなのかな？と思わせられたら、後の処理も理解してもらいやすいかも。

# step2

- numric_limits<int>::min()を-1に変更しただけ。

# step3

- 今思いついたけど、last_day_priceを無限にしておけば、絶対買値更新から始まるから、それでよくない？
- これでいこう

```cpp
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

```

1. 3分6秒

やり方上のに変える。

1. 2分48秒
2. 2分53秒 ここで、pricesが空のときのことを、考えなくてもいいことに気づいた。
3. 2分05秒
