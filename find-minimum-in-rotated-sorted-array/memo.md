# step1

- 考えてわからなかったので、答えを見た。

- また、左端(left)と右端(right)と真ん中(middle_pos)を見て、
  - nums[middle_pos] <= nums[right]なら、その間は昇順になっている。
    - 今度は、[left, middle_pos]で探す。middle_posは最小値である可能性がある。
    - なぜ (middle_pos, right]に最小値がないと言えるかというと、もし途中で最小値があるなら、それより左側は必ずどの
      右側の値より大きくないといけないから。つまりnums[right] > nums[middle_pos]でないといけなくて、
      これは矛盾している。
      - 単純に、昇順を保っているから、という理由でもいいかな？
        - 昇順の、右上がりの折れ線グラフをイメージすると、それを途中で切って、左側にそのグラフをもってくるイメージだから、nums[middle_pos] <= nums[right]なら、その範囲は昇順であると言っていい。
  - nums[middle_pos] > nums[right]なら、middle_posとrightのどこかのタイミングで、最小値が現れている。
    - (middle_pos, right]で探す。(middle_posはrightの位置の数字より大きいので、最小値ではないと明らかにわかる。)

  - ちゃんと終了するのか？
    - middle_posは[left, right]の範囲で決まる。
      - right = middle_posでleftと一致するのは、要素が2つだけになって、leftがmiddle_posに選ばれるとき。
      - left = middle_pos + 1は、同じくleftがmiddle_posに選ばれたとき、nums[left]のが大きかったら。
  - 範囲は、left <= rightだけど、等号が成り立てば最小値はでているので、left < rightがループの条件

- left, rightはそれぞれ何を表すのか。
  - [left, right]の範囲が、最小値が存在する可能性がある範囲。

  - [left, right]のなかの要素がただ1つに決まれば、最小値が決定する。

```cpp
#include <vector>
class Solution {
 public:
  int findMin(const std::vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    while (right - left > 0) {
      int middle_pos = left + (right - left) / 2;

      if (nums[middle_pos] <= nums[right]) {
        right = middle_pos;
      } else {
        left = middle_pos + 1;
      }
    }
    return nums[left];
  }
};
```

# step2

- https://github.com/seal-azarashi/leetcode/pull/39#discussion_r1846593786
  - 入力は、最小値を境界として、昇順を保っている。 [A, (最小値を含む)B]。A, Bはともに昇順を保つ。
    (Aがからの配列であることもある)
  - left, rightという変数を考える。最小値の可能性がある範囲を[left, right]として考える。
    leftとrightは、left < right という不変条件を満たさなければならない。
    left < rightのとき、[left, right]の要素数は2つ以上あることになるので、最小値の場所を特定するための
    計算をする必要がある。
  - ループを回すときに、middle_posという位置について計算する。それは、
    left <= middle_pos < rightという大小関係をもつ。
  - middle_posでの値によって、left, rightを更新すると、不変条件を満たしたままにできる。
    1. nums[middle_pos] <= nums[right]
      middle_posの位置での値と、rightでの位置の値はこのような大小関係により、[middle_pos, right]は昇順になっていることがわかる。よって、middle_posの位置での値は最小になるかもしれないが、それより右側は大きいので必要ない。

      right = middle_posと更新する。このとき、left <= middle_posという関係性なので、left <= rightとなっても、よい。
      ただ、left == rightとなった場合はループが終了する。
    2. nums[middle_pos] > nums[right]
      このような大小関係より、middle_posより右の位置に最小値があることがわかる。nums[middle_pos] > nums[right]より明らかにmiddle_posは最小値ではないので、

      left = middle_pos + 1とする。
      このとき、middle_pos < rightより、middle_pos + 1 <= right、left <= rightとなる。
      1のパターンと同様に、left == rightの場合は最小値が見つかり、ループを抜ける。
  - left == rightでループを抜けることになる。
  - right - leftが狭義単調減少となるので、ループはかならず停止する。
    上のパターンに沿って書くと、
    1. middle_pos < rightより、right = middle_posと更新すると、right - leftは減少。
    2. left <= middle_posより、left = middle_pos + 1とすると、right - leftは減少。

- left, right, midddleがどういう変数なのかを改めて、考えてみる。
 
- 塔の考え方を使って、今回は、一番小さい数字を頂きにもつ塔を探したい。この地点を、仮にtarget_posとしよう
  - [start_pos, end_pos]という範囲が与えられるので、その中から最小値を探す作業をする。
  - わかっていることは、
    - 範囲A [start_pos, target_pos), 範囲B [target_pos, end_pos]
      はそれぞれ、昇順になっている。
    - 範囲Aの要素は、範囲Bのどの要素よりも大きい。

  - 作業内容としては、
    1. 調べる塔を決める。その塔の位置を、middle_posと呼ぼう。名前の通り、だいたい真ん中を選ぶ。
      - middle_pos = (start_pos + end_pos) / 2
    2. nums[middle_pos]とnums[end_pos]を比べる。
      1. nums[middle_pos] <= nums[end_pos]なら、その間は昇順が保たれていることになる。
        - その中で一番小さいのは、nums[middle_pos]。それより左に最小値があるかもしれないので、
        - 次は、[start_pos, middle_pos]で調べたい。
        - 今回の問題では、同一の番号は出てこないけど、そうであるとき、等号をこちらに含めて良い。
          [..., 5, 5, 5, 7, ...]のようなとき。広義単調増加だね。
      2. nums[middle_pos] > nums[end_pos]なら、middle_posより後に最小値がある。
        - [middle_pos + 1, end_pos]を調べたい。middle_posの塔はまず最小ではない。

  - 結局これやってることとしては、昇順関係を使って、最小値でないものを削っていっている。だから、
    - [start_pos, end_pos]の間の要素がどんどん減っていかないとだめ。
    - それで、start_pos == end_pos, つまりただ1つの場所が導かれたら、そこが最小値。

  - あと、作業内容の前提として、middle_pos < end_posでないといけないところが重要。
    - / 2で切り上げと勝手にそうなっているので見落としがち。
    - 同じ塔の番号を比べるなんて、まずしない。

- 考えた上でもう一度step1のを書き下した。


## さまざまな種類

- https://github.com/seal-azarashi/leetcode/pull/39#discussion_r1849419449
  - この問いについて考えて、理解をさらに深めたい。

  1. 2で割る処理がありますがこれは切り捨てでも切り上げでも構わないのでしょうか。
  2. nums[middle] <= nums[right] とありますが、これは < でもいいですか。
  3. nums[right] は、nums[nums.size() - 1] でもいいですか。
  4. right の初期値は nums.length でもいいですか。

### o 1 [`切り捨てる`, `<=`, `nums[right]`, `length - 1`]

これは、step1で書いたコード。動いて、わかった。

### x 2 [`切り捨てる`, `<=`, `nums[right]`, `length`]

- パターン1とは、rightの初期値をlengthに変えた。
- これで、rightの意味合いが変わってくる。
  - まず、明らかなのは、nums[right]と比較をするときに、最初のループではオーバーフロー
  - これは、[left, right)が調べたい範囲だから。
  - まぁ、nums[right]が表すのは、絶対、最小値ではない左端といったところ。

- これでは、動かない。
- 動くように書き換えられるだろうか

```cpp
class Solution {
 public:
  int findMin(const std::vector<int>& nums) {
    int left = 0;
    int right = nums.size(); // not minimum
    while (right - left >= 2) {
      int middle = (left + right - 1) / 2; 
      // ↑ オーバーフローする可能性のある書き方だけど、今回はわかりやすく
      // left + ((right - 1) - left) / 2

      if (nums[middle] <= nums[right - 1]) {
        right = middle + 1;
      } else {
        left = middle + 1;
      }
    }
    return nums[left];
  }
};
```

- これなら、動いた。

### o 3 [`切り捨てる`, `<=`, `nums[length - 1]`, `length - 1`]

- 毎回毎回、nums[middle] <= nums[right]のようにrightの番号と比べるのではなく、毎回右端[length - 1]と比べる。
  - つまり、[middle, length - 1]までの広い意味での昇順が保証されているかどうかを見るということ。
  - [left, right]の範囲は小さくなっていかないといけないので、middle < length - 1であってほしい。

  - 切り捨て計算より、left <= middle < rightである。だから、middle == length - 1となることはない。
    1. <= なら、right = middle
    2. \> なら、left = middle + 1
  
  - これは、動くかな。

```cpp
class Solution {
 public:
  int findMin(const std::vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    while (left < right) {
      int middle = left + (right - left) / 2;

      if (nums[middle] <= nums[nums.size() - 1]) {
        right = middle;
      } else {
        left = middle + 1;
      }
    }
    return nums[left];
  }
};
```

- 動いた。

### o 4 [`切り捨てる`, `<=`, `nums[length - 1]`, `length`]

- 最初わかっていなくて、xだとおもっていたけど、動いた。

- nums[middle] <= nums[nums.size() - 1]を比べる。
  - rightは、一番端と同じか、それより小さいものの一番左端。
  - leftは、left未満は一番端より大きい。

  - 他の、[left, right]というような範囲の考え方ではなく、
  - [, left), [left, right) (<- 探す範囲), [right, ]

```cpp
class Solution {
 public:
  int findMin(const std::vector<int>& nums) {
    int left = 0;
    int right = nums.size();
    while (left < right) {
      int middle = left + (right - left) / 2;
      if (nums[middle] <= nums.back()) {
        right = middle;
      } else {
        left = middle + 1;
      }
    }
    return nums[left];
  }
};
```

### o 5 [`切り捨てる`, `<`, `nums[right]`, `length - 1`]

- 今回の問題の場合、ユニークな数字しか出てこないので、これでもACはする。動く
- ただ、[4(left), 5(middle), 5(right)]みたいなケースでは、左側に最小値があるのに、left = middle + 1として
  うまくできない。

### x 6 [`切り捨てる`, `<`, `nums[right]`, `length`]

- rightの初期値nums.size()

- nums[middle] < nums[right - 1]と比べないといけない。
- 動かない。

- 下なら、動く。
  - パターン2の<=を<にしただけ。 パターン5の理由でACする。ユニークな数字しか出てこないから。

```cpp
class Solution {
 public:
  int findMin(const std::vector<int>& nums) {
    int left = 0;
    int right = nums.size(); // not minimum
    while (right - left >= 2) {
      int middle = (left + right - 1) / 2;

      if (nums[middle] < nums[right - 1]) {
        right = middle + 1;
      } else {
        left = middle + 1;
      }
    }
    return nums[left];
  }
};
```

### o 7 [`切り捨てる`, `<`, `nums[length - 1]`, `length - 1`]

- これは、動く。
- ユニークな番号の集まりでかつ(<)、length - 1でないものをmiddleは選ぶから(left <= middle < right)。

- パターン3を<にしたコード

### x 8 [`切り捨てる`, `<`, `nums[length - 1]`, `length`]

- 動かない。
- これもまた、範囲調整をしないといけない (つまりすると動く)。
  - middleが調べたい範囲を全範囲取る可能性があるから。

### x 9 [`切り上げ`, `<=`, `nums[right]`, `length - 1`]

- 切り上げなので、left < middle <= rightである。
- middle == rightなことがあるので、これは動かない。
  - nums[middle] <= nums[right]が真なので、right = middleとなるが、永遠に範囲が減らない。

### x 10 [`切り上げ`, `<=`, `nums[right]`, `length`]

- left < middle <= rightになるけど、そもそも、rightは探索範囲ではない。

### x 11 [`切り上げ`, `<=`, `nums[length - 1]`, `length - 1`]

- middle == rightとなるため、動かない。

### x 12 [`切り上げ`, `<=`, `nums[length - 1]`, `length`]

- これも、動かない。rightは探索範囲ではない。

### x 13 [`切り上げ`, `<`, `nums[right]`, `length - 1`]

- 動かない。

### x 14 [`切り上げ`, `<`, `nums[right]`, `length`]

- 動かない 

### x 15 [`切り上げ`, `<`, `nums[length - 1]`, `length - 1`]

- 動かない。

### x 16 [`切り上げ`, `<`, `nums[length - 1]`, `length`]

- 動かない。

切り上げは、全部動かないな。
- right == middleとなって永遠にループがつづくのと、そもそもrightが探索範囲でない場合もある(それは切り捨てと同じ)。

# step3

1. 2分
2. 1分51秒
3. 