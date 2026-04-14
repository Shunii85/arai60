# step1

- 配列から、最も長い単調増加部分列の長さを求める。

- わからないな。手作業でもできない。
- とりあえず、わかっていることを考える。
  - 順番は変えてはだめ。
  - 途中の要素を消すことも消さないこともできる。
  - 部分列は、厳密に増加していないといけない。

- 一番考えられる、単純で遅いやり方は何だろう。
  - 1個ずつを部分列の先頭とする。
  - その次から順番に見ていく。
    - 数字が下がるときは、それは無視したい(つまり消す)。
    - だけど単純に無視すれば良いという話ではない。
    - なぜなら、[1, 2, 5, 3, 4]などの場合、5 => 3は下がるけど、2よりは大きいから、
      5を選ばずに3をとれば、その次4を取れる、というのがある。
    - だけどだからといって、どうとればいいのかわからない。
    - [1, 2, 5, 8, 10, 3, 4]ときた場合は、明らかに5, 8, 10とすてて3を選ぶより([1, 2, 3, 4]となる)
      [1, 2, 5, 8, 10]を選んだほうが良い。
    - 必ずしもなるべく小さい順に選べばいいというわけではない。

- 数字が書かれたコーンが100m間隔で並んでいて、そこを紐で結んでいく。
- もっとも長く紐を消費するようにしなきゃいけない。
- ただし紐を結ぶには、つなぐ前と後で、コーンの数字が大きくなっていなければいけない。
- コーンの数字はランダム。

- 答えを見た。下記LeetCodeの答えコピペ

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> res;

        for (int n : nums) {
            if (res.empty() || res.back() < n) {
                res.push_back(n);
            } else {
                int idx = binarySearch(res, n);
                res[idx] = n;
            }
        }

        return res.size();        
    }

private:
    int binarySearch(const vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }    
};

```

- 自分の考えてたこともあって、言わんとしていることはわかる。
- ただ、置き換えの意味がわからない。
  - 昇順を保つようにreplaceするとは？
  - たしかに、lengthがかわらないことはわかる。
  - 二分探索を使うらしい。

- 考えてわからなかったので[この説明](https://leetcode.com/problems/longest-increasing-subsequence/solutions/6092590/video-keep-elements-in-ascending-order-b-m5w0/) を読んでいるけど、ちょっとわかりずらかった。

- 少しGeminiと相談したあと、正直この子の説明もわかりずらかったけど、概ね以下のようなことをやりたいのだと思った。

- 数字を1つずつ見ていって、末尾より大きければ末尾に追加する。こうして、つなげて部分列を作っていく(これも本当はただのメモの過程)。
- 末尾より小さい数字の時、これはそれより前の数字のあとに繋げられる可能性がある。小さい数字を選んでおけば、より将来多くの数字を繋げられるようにできる。
  - 頭の数字を置き換えるときは、そこから始まる部分列を考える。

- 解説のプログラムでいうvector\<int> resは、あくまでもメモであることに注意。
  res[i]は、部分配列のi番目に格納できる最も若い数字。だけど終了した後に、resがLongest Increasing Sequenceを表すわけではない。

- 今回のBinary Searchは何のために使っているのかというと、末尾より小さい数字が来たときに、どこにそれを繋げられるか。
  - std::lower_boundでもできると思った。
  - なのでLowerBoundのような関数名にしたほうがわかりやすいと思った。何がしたいのかよくわからない。
    - 与えた引数、値n以上の最初の場所を返す。それより左側は、全部n未満
    - nより小さい場所の次がわかる。

```cpp
class Solution {
 public:
  int lengthOfLIS(std::vector<int>& nums) {
    std::vector<int> res;

    for (int n : nums) {
      if (res.empty() || res.back() < n) {
        res.push_back(n);
      } else {
        auto itr = std::lower_bound(res.begin(), res.end(), n);
        *itr = n;
      }
    }

    return res.size();
  }
};
```

# step2

- 自分でstep2-1.cppに1-1.cppを書き直してみた。

```cpp
class Solution {
 public:
  int lengthOfLIS(const std::vector<int>& nums) {
    if (nums.empty()) {
      return 0;
    }
    std::vector<int> memo;
    for (int n : nums) {
      if (memo.empty() || memo.back() < n) {
        memo.push_back(n);
      } else {
        int bound = LowerBound(memo, n);
        memo[bound] = n;
      }
    }
    return memo.size();
  }

 private:
  int LowerBound(const std::vector<int>& nums, int n) {
    int range_start = 0;
    int range_end = nums.size() - 1;
    while (range_start <= range_end) {
      int range_mid = (range_start + range_end) / 2;
      int middle = nums[range_mid];
      if (middle == n) {
        return range_mid;
      }
      if (n < middle) {
        range_end = range_mid - 1;
      } else {
        range_start = range_mid + 1;
      }
    }
    return range_start;
  }
};
```

- LowerBound、二分探索でできるのがいまいちよくわからないので、線形探索で実装してみる。
- 初めて、n以上になるところのindexを返せば、配列の左側がn未満になる。
  - n未満の次のmemoをnに更新したい

```cpp
 private:
  int LowerBound(const std::vector<int>& nums, int n) {
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] >= n) {
        return i;
      }
    }
    return 0;
  }
```

- 開区間で書くと自分のなかではわかりやすかった。これを採用しようかな。

```cpp
 private:
  int LowerBound(const std::vector<int>& nums, int n) {
    assert(nums.size() > 1);
    int finded_as_smaller = -1;
    int finded_as_larger = nums.size();
    while (finded_as_smaller + 1 < finded_as_larger) {
      int range_start = finded_as_smaller + 1;
      int range_end = finded_as_larger - 1;

      int middle_position = (range_start + range_end) / 2;
      int middle = nums[middle_position];
      if (middle == n) {
        return middle_position;
      }
      if (middle < n) {
        finded_as_smaller = middle_position;
      } else {
        finded_as_larger = middle_position;
      }
    }
    return finded_as_larger;
  }
```

## 最終

```cpp
#include <cassert>
#include <vector>
class Solution {
 public:
  int lengthOfLIS(const std::vector<int>& nums) {
    if (nums.empty()) {
      return 0;
    }
    std::vector<int> memo;
    for (int n : nums) {
      if (memo.empty() || memo.back() < n) {
        memo.push_back(n);
        continue;
      }
      int bound = LowerBound(memo, n);
      assert(bound != -1);  // memo.back() >= n
      memo[bound] = n;
    }
    return memo.size();
  }

 private:
  // return -1 if any element in nums is smaller than n.
  int LowerBound(const std::vector<int>& nums, int n) {
    int finded_as_smaller = -1;
    int finded_as_larger = nums.size();
    while (finded_as_smaller + 1 < finded_as_larger) {
      int range_start = finded_as_smaller + 1;
      int range_end = finded_as_larger - 1;

      int middle_position = (range_start + range_end) / 2;
      int middle = nums[middle_position];
      if (middle == n) {
        return middle_position;
      }
      if (middle < n) {
        finded_as_smaller = middle_position;
      } else {
        finded_as_larger = middle_position;
      }
    }
    if (finded_as_larger == nums.size()) {
      return -1;
    }
    return finded_as_larger;
  }
};

```



# step3

1. 6分17秒
2. 4分58秒
3. 4分41秒
