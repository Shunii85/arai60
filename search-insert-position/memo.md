# step1

- 与えられた値と同じ値をもつインデックスか、挿入位置を返すプログラム。
- O(logn)の時間計算量で書けとのこと。
- 二分探索。

- 書いた

```cpp
#include <vector>
class Solution {
 public:
  int searchInsert(const std::vector<int>& nums, int target) {
    int start = 0;
    int end = nums.size() - 1;
    while (start <= end) {
      int middle = (start + end) / 2;
      int num = nums[middle];
      if (num == target) {
        return middle;
      }
      if (num < target) {
        start = middle + 1;
      } else {
        end = middle - 1;
      }
    }
    return start; // または、end + 1
  }
};
```

- 自分にとっては、わかりやすい書き方を
  - targetよりも小さい方、大きい方の場所を記録する

```cpp
#include <vector>
class Solution {
 public:
  int searchInsert(const std::vector<int>& nums, int target) {
    int found_smaller_pos = -1;
    int found_larger_pos = nums.size();
    while (found_smaller_pos + 1 < found_larger_pos) {
      int start = found_smaller_pos + 1;
      int end = found_larger_pos - 1;
      int middle = (start + end) / 2;
      int num = nums[middle];
      if (num == target) {
        return middle;
      }
      if (num < target) {
        found_smaller_pos = middle;
      } else {
        found_larger_pos = middle;
      }
    }
    return found_smaller_pos + 1; // または、found_larger_pos
  }
};
```

- もうひとパターン
  - 下のプログラムだけ、num == targetを書いていないが、それでも上のプログラムもすべて動作する。

```cpp
#include <vector>
class Solution {
 public:
  int searchInsert(const std::vector<int>& nums, int target) {
    int start = 0;
    int ended = nums.size();
    while (start < ended) {
      int end = ended - 1;
      int middle = (start + end) / 2;
      int num = nums[middle];
      if (num < target) {
        start = middle + 1;
      } else {
        ended = middle;
      }
    }
    return ended;  // または、start
  }
};
```

- 二分探索自体の考え方は、他の問題のときに理解することができたが、startやendが最終的にどういうインデックスになるの
  か、という理解はあやふやだったように思う。

- でも結局は、start, endをどのように更新するかに注目すれば、さほど難しい話ではないかな。
  - [start, end]のパターンについて考えてみる。
    - startは、middleの場所の値が、targetより小さい時、middle + 1に更新される。
      - つまり、startより前の位置では、targetより小さいことが保証される。
    - endは、middleの場所の値が、targetより大きいときに、middle - 1に更新される。
      - つまり、endより後の位置では、targetより大きいことが保証される。
  - [start, end]の範囲でtargetがみつからなければ、targetより大きい最初のところが挿入位置なので、end + 1もしくは、start。

  - でもこれって、start == end + 1ということだよな。本当にそう？ 隣り合っているのか？
    - middleが、startかendの位置なら、はみ出すことになる。
      1. start, endの2つしかなかったら、startがmiddleに選ばれる
        - middle + 1ならstartとendが被って2.のパターンへ
        - middle - 1なら、endより後がtargetより大きいことになる。
      2. start, endが1つをさすなら、start兼endがmiddleに選ばれる。
        - targetより大きかったら、end = start - 1に。startはそのまま。
        - targetより小さかったら、start = end + 1に。endはそのまま。


  - こういうのいちいち考えるのもな、、
  - 考えれば考えるほど、理解できているのか怪しく感じる。

# step2

- 今回は、半開区間のやつで書いてみる。

```cpp
#include <vector>
class Solution {
 public:
  int searchInsert(const std::vector<int>& nums, int target) {
    int start = 0;
    int found_same_or_larger = nums.size();
    while (start < found_same_or_larger) {
      int end = found_same_or_larger - 1;
      int middle = (start + end) / 2;
      int num = nums[middle];
      if (num < target) {
        start = middle + 1;
      } else {
        found_same_or_larger = middle;
      }
    }
    return found_same_or_larger;
  }
};

```

# step3

1. 1分42秒
2. 1分32秒
3. 1分37秒
