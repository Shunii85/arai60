# step1

- 船に荷物を運び込んで、別の港へ運ぶ。
- ある期間(days日)ですべての荷物を別の港へ運び込む必要があるとき、どれだけ(なるべく少ない量で済む)の
  荷物が詰める船が必要か。

## 解法1

- 基本方針としては、
- 「操作」: 隣同士の荷物を足し合わせて、和が最小になる組を、1つの荷物にまとめ上げる。
- この操作を1回行うごとに、荷物のまとまりは1つ減る。
- これを、(荷物の数 - n日)回、実行すると、荷物のまとまりのうち、最大の容量のまとまりがわかる。
  その容量が、船に必要な最低限の容量となる。

- ただし、これは実行時間に間に合うかどうかは怪しい。
- 荷物の数をN、日数はDとしよう。
  - 「操作」ごとに、隣同士の足し算とその最小を求めるための時間計算量はO(N)
  - 操作の回数は、N - D回。
- よってO(N^2)

N(max) = 5 * 10^4なので、2.5 * 10^9

とりあえず、書いてみる。遅くてもいいから。

- 自分でかけなかったからgeminiに書いてもらったけど、だめだったコード。
```cpp
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int n = weights.size();
        
        // 荷物の数が日数以下の場合はまとめる必要がないため、単体の最大容量が答え
        if (n <= days) {
            int max_capacity = 0;
            for (int w : weights) {
                max_capacity = max(max_capacity, w);
            }
            return max_capacity;
        }

        // 実行する操作の回数: (荷物の数 - n日) 回
        int operations = n - days;

        for (int k = 0; k < operations; ++k) {
            // 隣同士の和が最小になる組を探す
            int min_sum = weights[0] + weights[1];
            int min_index = 0;

            for (size_t i = 1; i < weights.size() - 1; ++i) {
                int current_sum = weights[i] + weights[i + 1];
                if (current_sum < min_sum) {
                    min_sum = current_sum;
                    min_index = i;
                }
            }

            // 和が最小になる組を1つの荷物にまとめ上げる
            weights[min_index] = min_sum;
            // まとめられたもう片方の要素を配列から削除する
            weights.erase(weights.begin() + min_index + 1);
        }

        // 残った荷物のまとまりのうち、最大の容量を求める
        int result = 0;
        for (int w : weights) {
            result = max(result, w);
        }

        return result;
    }
};
```
- そもそも、最小の組み合わせがいくつもあると考えると、うまくいかない。

## 解法をLeetCodeで見る。

- 一番小さい容量は、weightsのなかで最大の荷物の容量、最大の容量はweightsの合計。
- このなかから、二分探索で、days以下の日数で探せる最小の容量を求めるという方針。

```cpp
#include <algorithm>
#include <numeric>
#include <vector>
class Solution {
 public:
  int shipWithinDays(const std::vector<int>& packages, int days) {
    int low_capacity = *std::max_element(packages.begin(), packages.end());
    int high_capacity = std::accumulate(packages.begin(), packages.end(), 0);
    int min_capacity = 0;
    while (low_capacity <= high_capacity) {
      int capacity = low_capacity + (high_capacity - low_capacity) / 2;
      if (ShipDays(packages, capacity) <= days) {
        min_capacity = capacity;
        high_capacity = capacity - 1;
      } else {
        low_capacity = capacity + 1;
      }
    }
    return min_capacity;
  }

 private:
  int ShipDays(const std::vector<int>& packages, int ship_capacity) {
    int days_needed = 0;
    int package_group_weight = 0;
    for (const auto weight : packages) {
      if (package_group_weight + weight > ship_capacity) {
        ++days_needed;
        package_group_weight = weight;
      } else {
        package_group_weight += weight;
      }
    }
    return ++days_needed;
  }
};
```

- 考えながら書いてACはできた。
- この手の問題、組み合わせを出力することもできるけど、それよりも組み合わせは必要ないけど結果だけ必要なら、全部のパターンを試すという方法も、よく使われる気がする。
- どうやって最小の荷物の分け方を考えようとするのだけど、そうしなくてもいい場合がある。このような考え方もできるようにしたい。

# step2

この人のを読んでおいた。

- https://github.com/dxxsxsxkx/leetcode/pull/44/changes

- ++days_neededの書き方が少し気に入らない。初期値を1としている人もいるけれど、packages.size()が1以上であればそれでいいのか。

- ShipDaysの書き方を少し変えた。elseを使わずに、capacityを超えるときは、一旦package_group_weight = 0;にしてから、pakcage_group_weight += weightとするとすっきりする。
- 荷物を積み込むときに超えそうになったら、一旦出荷して、また新しく積み込む。
- 最後はむしろdays_neededの初期値を1にするより、最後の荷物について処理を行わないので、++days_neededを返すほうが自分はわかりやすかった。

```cpp
class Solution {
 public:
  int shipWithinDays(const std::vector<int>& packages, int days) {
    int low_capacity = *std::max_element(packages.begin(), packages.end());
    int high_capacity = std::accumulate(packages.begin(), packages.end(), 0);
    int min_capacity = 0;
    while (low_capacity <= high_capacity) {
      int capacity = low_capacity + (high_capacity - low_capacity) / 2;
      if (ShipDays(packages, capacity) <= days) {
        min_capacity = capacity;
        high_capacity = capacity - 1;
      } else {
        low_capacity = capacity + 1;
      }
    }
    return min_capacity;
  }

 private:
  int ShipDays(const std::vector<int>& packages, int ship_capacity) {
    int days_needed = 0;
    int package_group_weight = 0;
    for (const auto weight : packages) {
      if (package_group_weight + weight > ship_capacity) {
        ++days_needed;
        package_group_weight = 0;
      }
      package_group_weight += weight;
    }
    return ++days_needed;
  }
};

```

# step3

1. 6分45秒
2. 5分44秒
3. 5分17秒 ShipDaysから、DaysForShipmentにメソッド名を変更した。なんか動詞になっていて違和感を感じた。
