# step1

- 前回の、House Robberで、通りに沿って並んでいる家ではなくて、円環に並んでいる家に強盗をしかけていく。
  - つまり、最初の家と最後の家は隣同士であるということ。

- 最初の家に強盗に入ったかどうかさえわかれば、できそう。
  - 強盗していって、最後の家にしかけるぞってなったときに自分が最初の家に強盗していれば、無理だなってことがわかる。

- なんかよくわからなくなってきた。
  - コードが複雑になって書き方がわからなくなったというのもそうだし、最初の家に強盗したかどうかで道中の盗めた最大の金額も変わってくると思い始めた。

- LeetCodeの答えを見た。
  - 最初か最後を省いた2つの配列について考える。そもそも、1つ目を訪れる可能性があるなら、最後は候補から外すという考え方だ。

---

- 答えみたのと同時に、自分なりに書き換えた。
  - いわれてみればシンプルな考え方だけど、思いつかなかった。自分が思いついたやり方は複雑だし、できなかった。

```cpp
#include <vector>
class Solution {
 public:
  int rob(const std::vector<int>& nums) {
    if (nums.empty()) {
      return 0;
    }
    if (nums.size() == 1) {
      return nums[0];
    }
    return std::max(robHelper(nums, 0, nums.size() - 1),
                    robHelper(nums, 1, nums.size()));
  }

 private:
  int robHelper(const std::vector<int>& nums, int from, int to) {
    int maximum_not_robbed_neighbor = 0;
    int maximum = 0;
    for (int place = from; place < to; ++place) {
      int robbed_here = maximum_not_robbed_neighbor + nums[place];

      maximum_not_robbed_neighbor = maximum;
      maximum = std::max(maximum, robbed_here);
    }
    return maximum;
  }
};
```

# step2

- コメント集を読んだ
  - https://github.com/TakayaShirai/leetcode_practice/pull/35#discussion_r2929595782
  - わりとすんなりこの考え方は理解ができた。
  - step1の段階で自分が考えていたことと、少しにていたからだ。
  - この考え方を素直に書き直すと、1つのループの中で書けるのでは？そのほうが自然に感じる。
    - ただそうなると実際少しややこしい
    - 2つに分けたほうが良いのかな。
      - 1つ目盗んだときの、1つ前盗んだか盗んでいないか
      - 1つ目盗んでいないときの、1つ前盗んだか盗んでいないか
    - 2つに場合分けするのは、要するにどんなバインダーを先に処理するかを考えるということ。

```cpp
#include <tuple>
#include <vector>
class Solution {
 public:
  int rob(const std::vector<int>& nums) {
    // each tuple contains
    // the first => maximum money, robbed there.
    // the second => maximum money, not robbed there.
    if (nums.empty()) {
      return 0;
    }
    std::tuple<int, int> first_house_robbed(nums[0], 0);
    std::tuple<int, int> first_house_not_robbed(0, 0);
    for (int place = 1; place < nums.size(); ++place) {
      const int money = nums[place];

      auto [max_robbed, max_not_robbed] = first_house_not_robbed;
      int robbed = max_not_robbed + money;
      int not_robbed = std::max(max_not_robbed, max_robbed);
      first_house_not_robbed = {robbed, not_robbed};

      if (place == nums.size() - 1) {
        continue;
      }
      auto [max_robbed_with_first, max_not_robbed_with_first] =
          first_house_robbed;
      robbed = max_not_robbed_with_first + money;
      not_robbed = std::max(max_not_robbed_with_first, max_robbed_with_first);
      first_house_robbed = {robbed, not_robbed};
    }
    // max candidates
    auto [max1, max2] = first_house_not_robbed;
    auto [max3, max4] = first_house_robbed;
    return std::max(std::max(max1, max2), std::max(max3, max4));
  }
};
```

- 整理した

```cpp
#include <tuple>
#include <vector>
class Solution {
 public:
  int rob(const std::vector<int>& nums) {
    if (nums.empty()) {
      return 0;
    }
    // each tuple contains
    // the first => maximum money, robbed there.
    // the second => maximum money, not robbed there.
    std::tuple<int, int> maybe_first_house_robbed(nums[0], 0);
    std::tuple<int, int> first_house_not_robbed(0, 0);
    for (int place = 1; place < nums.size(); ++place) {
      const int money = nums[place];
      updateMaximums(first_house_not_robbed, money);
      if (place == nums.size() - 1) {
        continue;
      }
      updateMaximums(maybe_first_house_robbed, money);
    }
    // max candidates
    auto [max1, max2] = first_house_not_robbed;
    auto [max3, max4] = maybe_first_house_robbed;
    return std::max(std::max(max1, max2), std::max(max3, max4));
  }

 private:
  void updateMaximums(std::tuple<int, int>& robbed_info, int money) {
    auto [robbed_maximum, not_robbed_maximum] = robbed_info;
    int robbed = not_robbed_maximum + money;
    int not_robbed = std::max(robbed_maximum, not_robbed_maximum);

    robbed_info = {robbed, not_robbed};
  }
};
```
# step3

1. 5分59秒
2. 5分41秒
3. 5分39秒
