# step1

以下のルールに則って、n行のテーブルを作成する。

- 1行目は、必ず0
- 2行目以降は、前の行に対して、
  - 0 => 01
  - 1 => 10
  に変換して作る。

- その結果、n行目の前からk番目のシンボル(0 or 1)を答える。

## 解法1

- しばらく何行か書き出してみて、2行目が01になるけど、そこからは半分で区切って見比べるとビット反転の関係であることがわかる。
- そもそも、0 => 01, 1 => 10なので、これはビット反転の関係にある。

- だから、前の行を次の行の先頭に持ってきて、さらに反転したものを右に置くと、その行が完成する。

- でも、最終的に2^(n - 1)個のシンボルが出てくるから、領域的に難しそうと気がづく。kが与えられているから、
  kだけ符号が作れたら、そこで終了することで多少は高速化可能。

---

答えを見た。

- 同じ考え方でやってる人がいたので、それを参考に。
- ある行について、前の行のコピーと、反転させたものによって構成される。
- これを利用して、1行目(0のみ)をどれだけ反転させたのか知る。

- k番目がn/2番目よりあとなら、それは前の行を反転させたもの。
- oooookoo (oが0 or 1. kはk番目)
- okoo (反転)
- ok (反転されたまま)
- k (反転されなかった)
よって k = 0

```cpp
class Solution {
 public:
  int kthGrammar(int n, int k) {
    bool reversed = false;
    int num_nth_symbols = 1 << (n - 1);

    while (num_nth_symbols > 1) {
      num_nth_symbols /= 2;
      if (k > num_nth_symbols) {
        reversed = !reversed;
        k -= num_nth_symbols;
      }
    }

    return !reversed ? 0 : 1;
  }
};
```

- 再帰でも書いてみた。
- ヘルパーを使って書くと、前の行のものを反転するか、しないかという作業がはっきりとわかりやすい。
- XORのビット反転で、書いたので、さっきみたいにreversedの意味よりわかりやすい。

```cpp
class Solution {
 public:
  int kthGrammar(int n, int k) { return Helper(1 << (n - 1), k); }
  int Helper(int num_symbols, int k) {
    if (num_symbols == 1) {
      return 0;
    }
    if (k > num_symbols / 2) {
      return Helper(num_symbols / 2, k - num_symbols / 2) ^ 1; // もしくは ~Helper()
    } else {
      return Helper(num_symbols / 2, k);
    }
  }
};
```

- 時間計算量 O(N) ( = O( log(2^N) ))

## 解法2

- 0 => 01, 1 => 10というふうにシンボルを生成する規則がある。
- このとき生成された側からみて、生成したシンボルを親とする。
  - 例えば、0110という列に対して、01101001が生成される。
  - このとき左から[0, 1]の親は0, [1, 0]の親は1という風になる。

- この親、生成元のシンボルを知り、それの左側か右側かを知ることでk番目のシンボルを知ることができるという考え方
  もある。

```cpp
#include <cmath>
class Solution {
 public:
  int kthGrammar(int n, int k) {
    if (n == 1) {
      return 0;
    }
    int parent = kthGrammar(n - 1, std::ceil(k / 2));
    bool odd_indexed_position = k % 2 == 1;
    if (parent == 1) {
      return odd_indexed_position ? 1 : 0;
    } else {
      return odd_indexed_position ? 0 : 1;
    }
  }
};
```

- 一瞬親のポジションの求め方に戸惑ったが、2個のシンボルのグループに分けることをイメージした。
  - 例えば4つのシンボルがあって、4番目の親はどのポジションか知りたければ、
    4 / 2 = 2で、4番目含めて2つずつのシンボルに分けようとすると2つのグループができる。2つ目に属しているとわかる。
  - では3番目のシンボルは？
    3 / 2 = 1.5 で、1つのグループと、0.5、つまり1人しかいないグループができた。なので、2つ目に属しているとわかる。
    これは、ceilを使えばわかる。
    もしくは、(k + 1) / 2でも表現できる

# step2 

- ビット反転の関係を利用した、再帰での書き方を採用する。
- わざわざヘルパー関数を用意する必要もなかったので、ひとつにまとめる。

```cpp
class Solution {
 public:
  int kthGrammar(int n, int k) {
    if (n == 1) {
      return 0;
    }
    int num_symbols = 1 << (n - 1);
    if (k > num_symbols / 2) {
      return 1 ^ kthGrammar(n - 1, k - num_symbols / 2);
    } 
    return kthGrammar(n - 1, k);
  }
};
```

# step3

1. 2分17

2. 2分21秒

2回目書きながら、こっちの表現のほうがしっくりくるなと思って、変えた。

```cpp
class Solution {
 public:
  int kthGrammar(int n, int k) {
    if (n == 1) {
      return 0;
    }
    int previous_row_num_symbols = 1 << (n - 2);
    if (k > previous_row_num_symbols) {
      return 1 ^ kthGrammar(n - 1, k - previous_row_num_symbols);
    }
    return kthGrammar(n - 1, n);
  }
};
```

3. 1分13秒
4. 
