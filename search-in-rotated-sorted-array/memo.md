# step1

昇順かつ、回転させた配列の中から、targetの位置を探す。

[1, 2, 3, 5, 6]を2回転させると、[5, 6, 1, 2, 3]

- [left, right]を探す。
- left <= middle < rightとなるmiddleを決める。
  - nums[middle] == target なら、middleを返す。

  - nums[middle] < targetなら、nums[middle]より大きい数字を探したい。
    - nums[middle] <= nums[right]かつ、target <= nums[right]なら右側。
    - nums[middle] <= nums[right]かつ、target > rightなら、左側。
    - nums[middle] > nums[right]なら、右側。なぜなら、回転していることがわかる。左側はnums[middle]より小さい。

  - nums[middle] > targetなら、nums[middle]より小さい数字を探したい。
    - nums[middle] <= nums[right]なら、左側。大きい数字側はいらない。
    - nums[middle] > nums[right]かつ、target <= nums[right]なら、右側。
    - nums[middle] > nums[right]かつ、target > nums[right]なら、左側。
 
 - 一応解けたけど、二分探索ができる前提で、無理やりどちらサイドを選ぶべきかを考えただけ。

 ```cpp
#include <vector>
class Solution {
 public:
  int search(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
      int middle = left + (right - left) / 2;
      if (nums[middle] == target) {
        return middle;
      }
      if (nums[middle] < target) {
        if (nums[middle] <= nums[right] && target > nums[right]) {
          right = middle - 1;
          continue;
        }
        left = middle + 1;
      } else {
        if (nums[middle] > nums[right] && target <= nums[right]) {
          left = middle + 1;
          continue;
        }
        right = middle - 1;
      }
    }
    return -1;
  }
};
```

- 答えを見ると、middleで分割するとき、左側と右側のどちらが昇順な区間かを見るらしい。
  - nums[left] <= nums[middle]なら、左側は昇順。ほんとに？ left == middleがあるにはあるけど。
    それは問題にならないのかな。
    left, rightの2要素のみのとき、middleにleftが選ばれる。そうすると、nums[left]か、nums[right]かになるので、それでいいか。
  - nums[left] > nums[middle]なら、左側は昇順ではない。途中で最小値を挟んでいる。
    なので、[middle, right]は昇順

  - 昇順の区間がわかったら、その区間内にtargetがあるかどうかを確認する。
    あったら、その区間のほうを選んで、どうじゃなかったら反対サイドの区間を選ぶ。

```cpp
#include <vector>
class Solution {
 public:
  int search(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
      int middle = left + (right - left) / 2;
      if (nums[middle] == target) {
        return middle;
      }
      if (nums[left] <= nums[middle]) {
        // < nums[middle]でいい。nums[middle] == targetではない。
        if (nums[left] <= target && target <= nums[middle]) {
          right = middle;
          continue;
        }
        left = middle + 1;
      } else {
        // nums[middle] < でいい。nums[middle] == targetではない。
        if (nums[middle] <= target && target <= nums[right]) {
          left = middle;
          continue;
        }
        right = middle - 1;
      }
    }
    return -1;
  }
};
```

# step2

- 他の人のコードを読む。
  - https://github.com/Yoshiki-Iwasa/Arai60/blob/7a893aebf11bff8f85291e35d1fa34a789566df2/problems/src/search_in_rotated_sorted_array/step1.rs
    - 前回の最小値の問題のやり方で、最小値の場所を見つけておく。そうすると、[0, min_index], (min_index, nums.size() - 1]で昇順なので、それぞれに対して二分探索を考えればいい。


---

# テスト期間明け

テスト期間中は何もやっていなかったのでやり直す。

- LeetCodeの答えからやり書き直してみた。

```cpp
#include <vector>
class Solution {
 public:
  int search(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
      int middle = left + (right - left) / 2;
      if (nums[middle] == target) {
        return middle;
      }
      if (nums[left] <= nums[middle]) {
        if (nums[left] <= target && target <= nums[middle]) {
          right = middle;
          continue;
        }
        left = middle + 1;
      } else if (nums[middle] <= nums[right]) {
        if (nums[middle] <= target && target <= nums[right]) {
          left = middle;
          continue;
        }
        right = middle - 1;
      }
    }
    return -1;
  }
};
```

- else ifのところはelseで前は書いているけど、自分が認識しやすいように書いた。
- ここで最初この解き方がどういう考え方をするのかは理解できていたけど、else ifの`left = middle`で、
  これleft == middleだった場合無限ループするのでは？というふうに思って最初混乱した。
  けれど、そういう場合はnumsの範囲が指す部分列は[nums[left], nums[right]]というふうになっていて、
  [nums[left]], [nums[left], nums[right]]という左側/右側の配列に分けて考えている。ということは、左側は昇順である条件を満たして、でもそこにtargetが含まれなければleft + 1をleftとして次調べるようになっている。
  よって次のnumsの範囲が指す部分列は[nums[right]]のようになる。よって無限ループにはならない。

  これ、else ifだと、なんだかどちらかの場合しか起きないように見えるので、(実際には完全に昇順な範囲を指すときもあったりするのでそんなことはない)
  continueを使って書きたい。

```cpp
#include <vector>
class Solution {
 public:
  int search(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
      int middle = left + (right - left) / 2;
      if (nums[middle] == target) {
        return middle;
      }

      if (nums[left] <= nums[middle]) {
        if (nums[left] <= target && target <= nums[middle]) {
          right = middle;
          continue;
        }
        left = middle + 1;
        continue;
      }

      if (nums[middle] <= nums[right]) {
        if (nums[middle] <= target && target <= nums[right]) {
          left = middle;
          continue;
        }
        right = middle - 1;
      }
    }
    return -1;
  }
};
```

- で、right = middle, left = middle + 1, left = middle (left ≠ middle), right = middle - 1
  の行で、必ず[left, right]の範囲は減っていく。whileは有限回の実行。

- [left, right]は探したい範囲の意味で一貫性有り。

## step2

- 最小の数のindexを見つけて分割するやり方をしたい。

- テスト前に[step2](#step2)で読んだコードの考え方を思い出しながらやった。これがわかりやすい。
  - 余りの計算がこういうことに使えると学べた。

```cpp
#include <vector>
class Solution {
 public:
  int search(const std::vector<int>& nums, int target) {
    int offset = FindMinIndex(nums);
    int virtual_left = 0;
    int virtual_right = nums.size() - 1;
    while (virtual_left <= virtual_right) {
      int virtual_middle = virtual_left + (virtual_right - virtual_left) / 2;
      int middle = (virtual_middle + offset) % nums.size();
      if (nums[middle] == target) {
        return middle;
      }
      if (nums[middle] < target) {
        virtual_left = virtual_middle + 1;
      } else {
        virtual_right = virtual_middle - 1;
      }
    }
    return -1;
  }

 private:
  int FindMinIndex(const std::vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    while (left < right) {
      int middle = left + (right - left) / 2;
      if (nums[middle] <= nums[right]) {
        right = middle;
      } else {
        left = middle + 1;
      }
    }
    return left;
  }
};
```

## step3

- 最小値を見つけて昇順とみなせる範囲を使って単純な二分探索を行う方法、を採用することにする。

1. 6分30秒
2. 5分08秒
3. 4分32秒

- FindMinIndexの処理、前回の問題については、まだあまり腑に落ちたようで落ちていないなと思った。
