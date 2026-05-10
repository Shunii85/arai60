# step1

- coinsという、n円玉という、コインの種類が渡される。それぞれのコイン、硬貨は無限にあるとして、
  硬貨の枚数を最小にして払いたい。

- 単純に、1枚あたりの値段が大きいものを使えば、枚数は抑えることができる。
- [100, 10, 1]などの現実的な硬貨を考えると、順に何枚ずつ使うか考えればよいことだ。
- ただし、amount = 220, coins = [100, 80, 40]の場合、100円玉を先に2枚使ってしまうと、そもそも
  払い切ることができないということになってしまう。すべてを一枚ずつ使えば3枚で払える。

- 1枚ずつコインを足して、地道に払っていく。
- 0枚から初めて、まず、1枚コインを使う時、何円払えるかを記録する。
    - 保存するときは、枚数が最小のものを
  - 作れた値段は、候補として別の記録をとっておく。

- 最初、足し算の段階でオーバーフローしてしまって、int64_t(long long)を使うことになった。
  - あんまり、良い対処方法には思えない。
  - 入力(int)の範囲に閉じるような計算にしたかった。

```cpp
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
        int64_t added_one_coin = money + coin_kind; // intだとオーバーフローが起きる可能性有り
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
```

- オーバーフローの対策について。
  - そもそも、amountを超える価値のコインは、使えない
  - amount * 2までが格納できる型であれば、保証できる。

- というか、amountまでする必要ないから、forは、 money < amountでいいな。

```cpp
#include <algorithm>
#include <cstdint>
#include <limits>
#include <unordered_map>
#include <vector>
class Solution {
 public:
  int coinChange(const std::vector<int>& coins, int amount) {
    std::vector<int> coin_nums(amount + 1, -1);
    coin_nums[0] = 0;  // 0 can be made up without using any coins.
    for (int money = 0; money < amount; ++money) {
      const int num_coins = coin_nums[money];
      if (num_coins == -1) {
        continue;
      }
      for (int coin_kind : coins) {
        if (coin_kind > amount) {
          continue;
        }
        int added_one_coin = money + coin_kind;
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
```


---

LeetCodeの答えを見てみる。

## コメント集読む

- これは参考になった。
  - https://github.com/Yoshiki-Iwasa/Arai60/pull/54#discussion_r1739985190
  - 最初、coin_numsを、intの最大値で初期化すると楽だけど、見つからないという意味の-1で初期化していた。
    - そのために、少し扱いがややこしくなっていたので、配列を2つに分けるのも手だということがわかった。

- https://github.com/nittoco/leetcode/blob/b41bdc3320e7a25bbec52ce5cbde07126b95e059/coin_change/coin_change.md#step1
  - 二次元配列を使った方法。
  - 授業で見た、ナップザック問題みたいだ。
    - それでいうと、表を全部埋めればいいから、TLEするほどの解法ではない気がしたけれど。
  - 読んでみたわいいものの、何をしたいのかわかりづらかった。

- BFS わかりやすかった。コインの枚数をだんだん増やして確認していくのが良い。
  - 選択肢はどれだけ多くても、amountの数だけ。
  - 自分でも書いてみた。
    - ただ、思っていたよりも遅め。オーダー的には変わらないとは変わらないと思うけれど
    - vector/unordered_setの構築などもあるだろうか。

```cpp
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

```

- DFS こっちはめんどくさそう。
  - 最初に作られた値段が、その値段を作るための最小のコイン枚数とは限らない。

# step2

- 最初に書いたDPを使ってやる。
- 今回は、calculatedで、すでに作られたかどうかを管理するようにした。
- これとあわせて、min_coin_numsを、intの最大値で初期化することで、簡潔に書けた。

```cpp
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
```

# step3

1. 6分10秒
2. 4分8秒

```cpp
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
```

3. 3分54秒
