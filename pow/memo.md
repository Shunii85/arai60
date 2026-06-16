# step1

- pow(x, n)を実装する。

## 解法1

- 単純に頭からかけていく方法だと、O(N)の時間計算量がかかる。
2^31 ≒ 10^9 ステップかかる。1秒くらい。

- TLEした。

```cpp
#include <cmath>
class Solution {
 public:
  double myPow(double x, int n) {
    double power = 1;
    unsigned int times = std::abs(n);
    for (int i = 0; i < times; ++i) {
      power *= x;
    }
    return n >= 0 ? power : 1 / power;
  }
};
```

## 解法2

たとえばx^4だったら、x^2 * x^2だから、x^2を計算してあったら、それを使えばいいことがわかる。

だから、計算結果をキャッシュしておけば、計算量が減らせる。

- 結構な領域が必要になるか？

- n乗に対して、n/2(切り捨て(c++))乗, n - n/2乗で再帰実行する。あ、奇数と偶数で分ければいいかな。

```cpp
class Solution {
 public:
  double myPow(double x, int n) {
    long long times = n;
    if (n < 0) {
      times = -times;
      x = 1 / x;
    }
    return PowHelper(x, times);
  }
  double PowHelper(double x, long long n) {
    if (n == 0) {
      return 1;
    }
    if (n % 2 == 1) {
      return x * PowHelper(x * x, n / 2);
    }
    return PowHelper(x * x, n / 2);
  }
};
```

- これだと、計算量はO(log N)になる。(N: べき数)
- 少し、intの最小値の扱いに困った。最初absを使っていたけど、最小値の絶対値を取るとintの範囲を超えてしまうので、
  long longに先に代入してから、-1倍した。

## 解法3

- 解法2を、再帰を使わずに、whileで。
- と思ったけど、解法2と考え方は全然違った。
- 基本的な流れとして、x^20 = (x^2)^10 = ((x^2)^2)^5 = ((x^2)^2) * (((x^2)^2)^2)^2
- あるループのとき、最初 power * (base_num)^times がx^nになっている。
  - そこで、timesが奇数なら、power * base_num * (base_num)^(times - 1)にする。
  - (base_num)^(times - 1)の部分は、 (base_num^2)^((times - 1) / 2) と書き直せる

- 2のべき乗を指数とするときが一番わかり易い。
  x^8 = (x^2)^4 = ((x^2)^2)^2 = (((x^2)^2)^2)^1 = (((x^2)^2)^2)^1 * (((x^2)^2)^2)^0
  0乗は計算する必要なし。

- これもO(logN)

```cpp
class Solution {
 public:
  double myPow(double x, int n) {
    long long times = n;
    if (times < 0) {
      times = -times;
      x = 1 / x;
    }
    double power = 1;
    double base_num = x;
    while (times > 0) {
      if (times % 2 == 1) {
        power *= base_num;
      }
      base_num *= base_num;
      times /= 2;
    }
    return power;
  }
};
```

# step2

- 一番式変形がイメージしやすかったので、解法2を採用する。

- 変数名
- long longから、int64_tを使った。
  - https://www.cppreference.com/cpp/types/integer
  - ただ、int64_tは、optionalとある通り、処理系による。定義されていれば正確な64ビット。

```cpp
#include <cstdint>
class Solution {
 public:
  double myPow(double base_num, int64_t times) {
    if (times < 0) {
      base_num = 1 / base_num;
      times = -times;
    }
    return PowHelper(base_num, times);
  }
  double PowHelper(double base_num, int64_t n) {
    if (n == 0) {
      return 1;
    }
    if (n % 2 == 1) {
      return base_num * PowHelper(base_num * base_num, n / 2);
    }
    return PowHelper(base_num * base_num, n / 2);
  }
};
```

# step3

1. 2分41秒
2. 2分27秒
3. 2分1秒

