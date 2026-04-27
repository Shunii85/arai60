# step1

- 強盗をしかける。
- 隣同士の家を襲撃すると、互いに連携されたセキュリティーシステムで、警察に通報される。
- 通報されずに、つまり隣同士を訪れることなく、最大の利益を上げるように強盗を行う。

- [1, 0, 0, 1]とかの場合、1番目と3番目を選んだら1になってしまう。
  - 間の0を2つ飛ばせば2になる。必ずしも、次の次を選ぶわけではない。
  - [1, 0, 3, 1]だったら絶対[1, 3]を選んで4
  - お隣さんだけスキップして、それ以降見ていく。

- 未来を考えるのは難しいから、1個前の家より後ろ(2個前から)の中で、最も盗めている金額が大きいところに自分の金額を
  足して、考える。1個前までで盗める金額のほうが高いかもしれない。
- これを続けて、一番大きい値が、盗める最大の金額になるかな。

- 書けた。
- 最初、2個前と1個前で、それぞれmaxであることをどう保証しようか一瞬迷ったけど、次の人に託すときに、
  - new_two_backはtwo_backとone_backで大きい方を取ればいい。
  - new_one_backは、new_two_backと、currentの大きい方を取ればいい。
  - new_two_backのほう、後ろの方から考えて、更新していけばいい。

```cpp
#include <algorithm>
#include <vector>
class Solution {
 public:
  int rob(std::vector<int>& nums) {
    if (nums.size() == 0) {
      return 0;
    }
    int two_back_maximum = 0;
    int one_back_maximum = 0;
    int current = 0;
    for (int num : nums) {
      current = two_back_maximum + num;

      two_back_maximum = std::max(two_back_maximum, one_back_maximum);
      one_back_maximum = std::max(two_back_maximum, current);
    }
    return one_back_maximum;
  }
};
```

# step2

- もっと素直な変数名の付け方をしたい。
  - 今いる場所からお金を盗んだらどうなるか。
  - 今いる場所からお金を盗まなかったらどうなるか。

- コメント集を参考にした。
  - https://github.com/Yoshiki-Iwasa/Arai60/pull/50#discussion_r1717915563
    > 「伝言」の内容は「ここまで最大いくら取れる、俺の眼の前の家に盗みに入らないとすると最大いくら取れる」の二つだけじゃないですか。

- 前の人までの最大と、前の人が盗みに入らなかったときの最大を使う。
- 前の人が盗みに入らなかった場合、そこに今から盗む人のお金を足して、盗んだ場合の最大をmaxで更新する。
- 今の、盗みに入らなかった場合は、その前までのmaxを使えばいい。

# step3

1. 1分26秒
2. 1分22秒
3. 