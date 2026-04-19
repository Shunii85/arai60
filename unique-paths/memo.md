# step1

- m(column) * n(row)のgridが渡されて、左上のマスをスタートとして、右下のマスに到達するための道は何種類あるのか、という問題。

- 具体的に考えてみると
  - 1 * 1は簡単で1パターン
  - 1 * 2, 2 * 1も簡単で、1パターン
  - 2 * 2になると、右 => 下と下 => 右で2パターン

- ゴールの右下のマスだけでなく、近いマスで、いけるパターンがどれだけあるのかというのを考えることにする。
  - まず、1行目のマスに関しては、一度したに下がってしまったら行けないので、スタート地点からひたすら右に進まないといけないため、各マスに行くパターンは1パターンしかない。
  - 同様に1列目に関しても、1度右に行ってしまっては左に戻れないので、1パターン。

  - 2つの1パターンしかいけないのがわかったら、それ以外のマスのパターンを考えていく。
  - あるマスに注目した時、そこに移動するためのマスは、上と左に存在する。なぜなら下と右にしか動けないから。
    - だから、上のマス、左のマスのパターンを合わせて、そのマス目のパターンにする。
  - 現状、1行と1列のパターンが1ずつと決定しているので、それを利用して進めていく。
    - さきに1行1列を考えてもいいけど、最初の行/列なら1と考えてもいいな。
      - 最初の1列だけ埋める
      - 最初の1行だけ埋める
      - もあり


- 時間計算量、空間計算量ともにO(m * n)

- できた。

```cpp
class Solution {
 public:
  int uniquePaths(int m, int n) {
    if (!(m > 0 && n > 0)) {
      return 0;
    }
    std::vector<std::vector<int>> pattern_grid(m, std::vector<int>(n, 0));
    for (int row = 0; row < m; ++row) {
      pattern_grid[row][0] = 1;
    }
    for (int column = 0; column < n; ++column) {
      pattern_grid[0][column] = 1;
    }

    for (int column = 1; column < n; ++column) {
      for (int row = 1; row < m; ++row) {
        pattern_grid[row][column] =
            pattern_grid[row][column - 1] + pattern_grid[row - 1][column];
      }
    }

    return pattern_grid[m - 1][n - 1];
  }
};
```

# step2

- コメント集を読んだ感じ、1行もしくは1列分の配列でも解けるっぽい。
  - 確かに、自分のコードでは1列ごとしか注目していない。
- current_column[row]は、同じ行の一列前のパターン。
  - 左のパターン(old_current_column[row]) + 上のパターン(current_column[row - 1]) 

- 書けた。
  - 簡単に書けるし、1つの列(もしくは行)に着目するのは、自分でも頭の中に思い描いていたのでできた。
  - 1つ目のほうが直感的か？

```cpp
class Solution {
 public:
  int uniquePaths(int m, int n) {
    std::vector<int> current_column(m, 0);
    current_column[0] = 1;
    for (int _column = 0; _column < n; ++_column) {
      for (int row = 1; row < m; ++row) {
        current_column[row] += current_column[row - 1];
      }
    }
    return current_column.back();
  }
};
```

- https://github.com/olsen-blue/Arai60/pull/33/changes/BASE..a96dca4ab9409d456ccbf80ebb9051bbf345c2ce#diff-3d04158956739fa9e3948a043cdcf2a3246498baedcc5098bf90ee92cad790d0R100
  - なるほど再帰もあるのか
  - たしかに自分で、上のパターンと、左のパターンを足せばいいと書いていた
    - ゴールからたどれば良いのか
  - 計算量がわからないな。
    - 全部辿るから、同じくO(m * n)か？
    - 1行目と1列目はわかっているから、それより小さそう。
    - TLEしてしまった。
    - あ、Max Islandみたいな問題と違う、マス目ごとに1回ずつ呼び出されるわけではないんだ。
    - 組み合わせが出てくるらしい。わからん。
      - 木構造みたいになるのは理解できる。

```cpp
class Solution {
 public:
  int uniquePaths(int m, int n) {
    if (m == 1 || n == 1) {
      return 1;
    }
    return uniquePaths(m - 1, n) + uniquePaths(m, n - 1);
  }
};
```

- メモしたらとけた。

```cpp
#include <vector>
class Cache {
 public:
  Cache(int row, int column)
      : pattern_cache_(row, std::vector<int>(column, -1)) {}
  int add(int row, int column, int num) {
    return pattern_cache_[row][column] = num;
  }
  int get(int row, int column) { return pattern_cache_[row][column]; }
  bool contains(int row, int column) { return get(row, column) != -1; }

 private:
  std::vector<std::vector<int>> pattern_cache_;
};

class Solution {
 public:
  int uniquePaths(int m, int n) {
    Cache cache(m, n);
    return paths(m - 1, n - 1, cache);
  }

 private:
  int paths(int row, int column, Cache& cache) {
    if (row == 0 || column == 0) {
      return cache.add(row, column, 1);
    }
    if (cache.contains(row, column)) {
      return cache.get(row, column);
    }
    return cache.add(
        row, column,
        paths(row - 1, column, cache) + paths(row, column - 1, cache));
  }
};
```

# step3

1次元行列での解法を採用する。

1. 2分10秒
2. 1分56秒
3. 1分49秒
4. 1分40秒
