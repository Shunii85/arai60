# step1

- 2本目まではk^2パターンであることはわかる。
- 3本目以降、
  - 連続した色を塗った後か つまりk-1色しか塗れない
  - それ以外の後か つまりk色塗れる
- というふうになっていく。

- とりあえず、自分で紙に書いて一生懸命やってみた。
- 一応法則というか、どうやればいいかはわかってきた。
  - 3本目以降(= N)を考える。
  - 2本目までに関しては, kパターン, k^2パターンというのは明らか。
  - 現在注目したいのを、N番目として、a番目, b番目(= a + 1), N番目(= a + 2 >= 3)の3本に注目する。
  - 大事なのは、a, b番目の柱の色が被った場合とそうでない場合でわける
    - 被っている場合はN番目にk-1色塗れることがわかる
    - 被っていない場合はN番目にk色塗れることがわかる
  - 以下の3場面かな。
    1. ここで、どうしたら被っているパターンを数え上げられるのだろう？
      - a番目の柱のパターンを数えればよい。
      - a番目の柱のパターンの数がわかれば、それと同じになるb番目のパターンがかぶる。
        - aが[赤、赤、白、白、緑、緑、緑]のような塗れるパターンの場合
        - bも[赤、赤、白、白、緑、緑、緑]なら、かぶる。
        - よって、aのパターン数 * (k-1)すれば、N番目のポストの一部がわかる。
    2. 被っていないパターンを数え上げるには？
      - (b - a)パターン × kする。
    3. a番目とa-1番目が被っている場合(a >= 2, つまり2フェーズ目から)、a-1とbがかぶることはないので無条件に
      bのパターン数 × kとなる。

実装してみる。

---

- [step1-1.cpp](./step1-1.cpp)にTLEするが、おそらく書けた。
  - 指数関数的にパターンの幅が広がっていく。O(2^N)
- けれど、上の自分の考え方をすっきりとコードに書き表せたような気がしない。
- 3本にさえ注目すればできそうな気がするのに。

- LintCodeに制約がなく、実際の実行時間はよくわからなかった。

```c++
enum PREVIOUS_TYPE { DUPLICATED, NON_DUPLICATED };
class Solution {
 public:
  int numWays(int n, int k) {
    if (n <= 2) {
      // comment: n = 0のときにだめだな。
      return std::pow(k, n);
    }
    std::queue<std::tuple<PREVIOUS_TYPE, int>> q;
    q.push({DUPLICATED, k});
    q.push({NON_DUPLICATED, k * (k - 1)});
    int nth = 2;
    while (nth < n) {
      int pattern_wide = q.size();
      for (int i = 0; i < pattern_wide; ++i) {
        auto [type, prev_pattern_num] = q.front();
        q.pop();
        if (type == DUPLICATED) {
          q.push({NON_DUPLICATED, prev_pattern_num * (k - 1)});
        } else {
          q.push({DUPLICATED, prev_pattern_num});
          q.push({NON_DUPLICATED, prev_pattern_num * (k - 1)});
        }
      }
      ++nth;
    }
    int num_ways = 0;
    while (!q.empty()) {
      auto [_, num] = q.front();
      q.pop();
      num_ways += num;
    }
    return num_ways;
  }
};

```

## Geminiと相談

- 自分の書いたコードの無駄な部分を議論した。
- queueで指数的にパターンを広げていかなくても、2つの変数さえあればできるらしい。
- 今までは、直前2本がどうだったかに着目したが、それでは、さっきの自分の考えのa番目とa-1番目が被っていないことを保証するのが難しい。
- なので、直前と同じ色を塗りたいのか(same)、違う色を塗りたいのか(different)で話を分割することができる。
- ここでも注目したいN番目について、a, b, Nの三連番の支柱を導入して考えたい。
  - 直前(b)と同じ色を塗りたい場合(sameは)、直前の2本(a, b)が被っていない必要がある。
    - このためには、bのdifferentが、そのままパターン数になる。
    - これは、bがaと違う色を塗るパターンだから。
  - 直前(b)と違う色を塗りたい場合(differentは)、無条件に[bのsame + bのdifferent] × (k-1)になる。

- [step1-2.cpp](./step1-2.cpp)
  - 理解はしたと思うのだけど、なんとなく、こんなに簡潔に書けるのが不思議。
  - 前の人が違う色を塗ったパターンなのか、同じ色を塗ったパターンなのか、2つともその情報付きでくれれば確かに、それはわかりやすいか。
    - 支柱ごとに人が立っているとする。
    - ある人が作業を始める。
      - 直前の人が、さらに直前のポストと同じ色を塗るパターンの数と、違う色を塗るパターンの数を教えてくれた。情報にラベルづけをして、次の人渡されるとしよう。
        - same: 私が、直前の人のポストと同じ色を塗ったのは○パターン。
        - different: 私が、直前の人とは違う色で塗ったのは△パターン。
      - 自分も、same, differentを考えたい。
        - same (直前のポストと同じ色を塗るパターン)
          - 1本前の人が、すでに2本前の人と同じ色を塗るパターンなら、それは無理。
          - なので、1本前の人のdiffernetが、そのままsameになる。
        - different (直前のポストと違う色を塗るパターン)
          - これは、直前がどんな色で塗られるのでも関係ない。
            - 直前2本がダブっていようがいまいが、(k - 1)色で塗れる。
          - よって (same + different) * (k - 1)色が私のdifferentになる。
  - こんな感じかな
  - 時間計算量はO(N), 空間計算量はO(1)
  - 1億本( = 10^8 )くらいなら1秒程度でいけるかと。
 
 ```c++
class Solution {
 public:
  int numWays(int n, int k) {
    // comment: ここの早期リターンはなんか、整理したい気持ちもある。
    if (n == 0) {
      return 0;
    }
    if (n == 1) {
      return k;
    }
    if (n == 2) {
      return k * k;
    }
    int nth = 2;
    int same = k;
    int different = k * (k - 1);
    while (nth < n) {
      int prev_same = same;
      int prev_different = different;
      same = prev_different;
      different = (prev_same + prev_different) * (k - 1);
      ++nth;
    }
    return same + different;
  }
};
```


## 1つの漸化式で表せる方法

- これがなんとなく1番わからなかった考え方。
  - えと、one_back * (k - 1)は直感的で、直前のポストと違う色を塗るパターン。(k - 1)色塗れるからね。
  - two_back * (k - 1)に関しては、直前のポストと同じ色を塗るパターン。
    - このとき、two_back * (k - 1)は、別の意味では、直前のポストが、さらにその直前のポストと違う色を選択した場合のパターン数を表している。
    - このパターンのときに、two_backとone_backのポストが違う色で塗られているわけだから、one_backのポストと同じ色が塗れる。
    - two_backパターンに関しては、two_back と one_backが同じ色のパターン。
- [step1-3.cpp](./step1-3.cpp)に書いた。

```cpp
class Solution {
 public:
  int numWays(int n, int k) {
    if (n == 0) {
      return 0;
    }
    if (n == 1) {
      return k;
    }
    if (n == 2) {
      return k * k;
    }
    int nth = 2;  // now complete the num of patterns by 2th;
    int two_back = k;
    int one_back = k * k;
    int current = 0;
    while (nth < n) {
      current = one_back * (k - 1) + two_back * (k - 1);
      one_back = current;
      ++nth;
    }
    return current;
  }
};
```

# step2

- [step1-3.cpp](./step1-3.cpp)を採用した。
- whileはわかりにくかったので、for文にした。
- currentを求めるための式は、1つにまとめても良いと思う。
  - 好みかな?

```cpp
class Solution {
 public:
  int numWays(int n, int k) {
    if (n == 0) {
      return 0;
    }
    if (n == 1) {
      return k;
    }
    if (n == 2) {
      return k * k;
    }
    int two_back = k;
    int one_back = k * k;
    int current = 0;
    for (int nth = 3; nth <= n; ++nth) {
      current = one_back * (k - 1);   // chose different color from last;
      current += two_back * (k - 1);  // chose same color from last;

      two_back = one_back;
      one_back = current;
    }
    return current;
  }
};
```

# step3

1. 2分30秒
2. 1分44秒
3. 1分36秒
4. 1分37秒

# step4

- その後、小田さんにstep1-1.cppについてのコメントをもらった。
  - https://discord.com/channels/1084280443945353267/1478763507963924522/1492789469097492550
- たしかにそのとおりで、まとめられる。
- 雑に書き直してのがこれ
  - ここで、pattern_wideは常に2になるので、 queueが必要ないことがわかる。


```cpp
#include <cmath>
#include <queue>
#include <tuple>

enum PREVIOUS_TYPE { DUPLICATED, NON_DUPLICATED };
class Solution {
 public:
  int numWays(int n, int k) {
    if (n <= 2) {
      return std::pow(k, n);
    }
    std::queue<std::tuple<PREVIOUS_TYPE, int>> q;
    q.push({DUPLICATED, k});
    q.push({NON_DUPLICATED, k * (k - 1)});
    int nth = 2;
    while (nth < n) {
      int pattern_wide = q.size();
      int duplicate_pattern_num = 0;
      int non_duplicate_pattern_num = 0;
      for (int i = 0; i < pattern_wide; ++i) {
        auto [type, prev_pattern_num] = q.front();
        q.pop();
        if (type == DUPLICATED) {
          non_duplicate_pattern_num += prev_pattern_num * (k - 1);
        } else {
          duplicate_pattern_num += prev_pattern_num;
          non_duplicate_pattern_num += prev_pattern_num * (k - 1);
        }
      }
      q.push({DUPLICATED, duplicate_pattern_num});
      q.push({NON_DUPLICATED, non_duplicate_pattern_num});
      ++nth;
    }
    int num_ways = 0;
    while (!q.empty()) {
      auto [_, num] = q.front();
      q.pop();
      num_ways += num;
    }
    return num_ways;
  }
};
```
