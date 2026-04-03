# step1

- まず、height-balancedの意味がわからない。
  - 高さのバランスが取れている
  - > 二分木の高さのバランスが取れている（height-balanced）とは、二分木において、全てのノードの左右の部分木の高度差の絶対値が1以下であること。
    - 0か1か
  
- binary search treeとは、たぶん二分探索から来ている。
  - 二分探索可能な二分木ということだろうか？
  - 左の子 <= 親 <= 右の子という関係らしい。


何から、何がつくりたいのか
- 何から
  - 昇順の数列
- 何を
  - height-balancedな (任意のノードの左右の部分木の高さの差の絶対値が1 or 0)
  - 二分探索木 (左の子 <= 親 <= 右の子)


- 二分探索木を作れならまだわかるけど、高さの差を保証するように作るのは難しくない？

---

- 答えを見た。
- 考え方としては、
  - 中央値をピックすれば、
  - その左サイドと右サイドの配列の長さは、等しいか1ちがうかになる。
    - 配列の長さが奇数なら、
      - 左サイドと右サイドは同じ長さになる。
    - 配列の長さが偶数なら
      - どちらかのサイドの配列の長さが1多くなる。
- 途中の中央値のindexをピックするために
  ```cpp
    int middle = left + (right - left) / 2;
  ```
  という計算がある。  
  - geminiに説明を求めてみると、これは整数値のオーバーフローを防ぐためだという。
  - 今回の場合はnums.sizeが最大1万なので、1万 + 1万 = 2万より、intの範囲を超えることはない。
  - けれど、この計算方式を用いることで、left/rightがどちらもintの範囲を満たすときは、intの範囲外の値が途中で
  生成されることはない。
    - まず距離(left - right)の半分をもとめて、left + 距離の半分をすることで求めている。  
    - right - leftは当然rightより小さいし、left + 距離の半分も、rightより小さい。


- 時間計算量
  - O(N)
    - それぞれのノードに対してconvertを呼び出す。
- 空間計算量
  - O(N)
    - 再帰関数がスタックに積まれる: O(logN)
    - ノードを作る: O(N)

---

- そもそも、このmiddleの計算とベースケースの設定ですべてのindexが網羅できるのかいまいちわからない。
  - 現状の理解として
    - middleをピックして左サイドと右サイドに配列を分割すると、分割前の要素数が偶数 or 奇数でどのようになるか決まるということ。
      - 奇数の場合(2n + 1)、同じ要素数(n, n)で分割される。
      - 偶数の場合(2n), (n - 1, n)で分割される。
    - それぞれの場合について最小を考えると、
      1. 1の場合、わけるものはない。
        - middleとleft, rightは同じものになる。
        - [left, middle-1], [middle + 1, right]の範囲は逆転する
      2. 2の場合、(0, 1)にわかれる。
        - 実質的に、middleと最初の要素は重なる。
        - [left, middle - 1]の範囲は逆転する。左サイドがないことがわかる。
        - middle + 1, rightは同じになる。1.の場合へ行く。

## コメント集を見る

- ダブルポインタを使った解法
- あとで理解したい。

```cpp
class Solution {
 public:
  TreeNode* sortedArrayToBST(vector<int>& nums) {
    stack<tuple<TreeNode**, int, int>> parents_and_ranges;
    TreeNode *node;
    parents_and_ranges.emplace(&node, 0, nums.size());
    while (!parents_and_ranges.empty()){
      auto [parent_node_pointer, left, right] = parents_and_ranges.top();
      parents_and_ranges.pop();
      if (left >= right) {
        continue;
      }
      int mid = (left + right) / 2;
      TreeNode* parent_node = new TreeNode(nums[mid]);
      *parent_node_pointer = parent_node;
      parents_and_ranges.emplace(&parent_node->left, left, mid);
      parents_and_ranges.emplace(&parent_node->right, mid + 1, right);
    }
    return node;
  }
};
```

# step2

ほぼ変更なし。

# step3

1. 3分14秒
2. 3分5秒
3. 2分23秒
4. 2分21秒

- 書いていく中で、区間について理解していったかもしれない。
  - 現状、閉区間を関数に渡していて、つまりそれは、
    - left_iとright_iはどちらも含まれるということ。
    - left_iからright_iまでが、middleを求めるための区間
  - そして、left_iとright_iの関係として、
    - left_i <= right_iなら範囲の中に数字が含まれていることがわかる。
  - left_iからright_iの中からmiddleをピックしたら
  - middle_iを除外した2つの範囲について考えたい。
    1. left_iからmiddle_i - 1の範囲でピックしたい
    2. middle_i + 1からright_iの範囲でピックしたい
    ピックしたいけれど、そこに含まれるindexがなければ、つまり not (left_i <= right_i)ならば
    処理したい要素は存在しないのでnullptr

# step4

やはりちゃんと理解していない状態で書くのは良くない。

discordでつぶやいたところ、小田さんがヒントを出してくれたので、それをもとに考えてみる。

> 開区間・閉区間というのは「表現方法の話」で、実態とは別なんです

https://discord.com/channels/1084280443945353267/1478763507963924522/1489197021209559090


- わかったような気もする。
- ここで問題とは関係ないけれど、
- 二分探索だけに当てはまる話ではない、と書いてあった。
  - ではこんなふうに発想が他の問題でできるのですか？本当に？と聞きたくなってしまったが、
  - 逆に、このように解決できるような問題を人々が見つけて、適用させてきた、というほうが正しいのではないか？
  - だから、このような問題が解けるのは大したことではない、と言えるのではないか。


- ここで問題に戻ろう
- 開区間・閉区間というのは「表現方法の話」である。
  - その意味を途中で変えてはいけない。混乱が生まれる。
  - 共通認識を持つ。
- 閉区間の場合、ここから、ここまで確認してほしいよという話。
- 半開区間の場合、ここから確認してほしくて、ここは見なくてもいいよ、という話


- step4.cppに半開区間で書いてみる。
  - https://discord.com/channels/1084280443945353267/1478763507963924522/1489414086931255346
  - https://discord.com/channels/1084280443945353267/1478763507963924522/1489445700801396829


# step5

step3とほぼほぼ同じだけど変数名を変えて、意味を飲み込んでもう3回くらい書く。

1. 2分50秒
2. 2分12秒
3. 2分3秒

step4.cppを一回だけ書く。

1. 2分36秒
