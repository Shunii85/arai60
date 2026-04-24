# 考え方

- 二分木が与えられて、最大の深さを求める。
  - 解法
    1. 今までのグラフの問題のように、訪れていく方法
    2. 深さごとにノードの数は決まっている(2倍ずつ増えていく)ので、
      ノードの数を数えてそこから逆算する。
      - そもそも今考え方は無理だと気づいた。全部順番に埋められているわけではない。
      - というか配列が与えられるわけではなかった。
      - でも考えれてよかった。


## 解法1

- 訪れるにはどうすればいいか。
  - root[0]が根。
  - 右の子、左の子をみたい。
  - 配列で与えられていないので、普通にleftとrightのポインタを見ればいい
  - これの繰り返し。
  - BFS

## 解法2

これでは解けない。

- 二分木の深さ1から始めるとすると、
  - 1 + 2 + 4 + 6 + ...
  - 深さをdとして、
  - 等比数列とかの公式を使っていくと
  - d = log2(Sd + 1)となる。
    - ここでSdはノードの数。
  - 深さは当然1, 2, 3..と増えていくので
  - 整数の範囲で切り捨てればいい。

- この考え方から、
- すべて順番通りに二分木が埋まっていた場合、幅が大きくなる。
- 1万個ノードがあって、順番に埋めていくと深さが13程度になるので、
- 1つの深さ最大4000個ほどのノードをもつ。
- 解法1のやり方で、最大4000個程度格納すると思っておくといい。

---

# step1


## step1-1.cpp

- 解法1をもとに自分で実装。

```cpp
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

class Solution {
 public:
  int maxDepth(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    }
    std::unordered_set<TreeNode*> same_depth_nodes{root};
    int depth = 0;
    while (!same_depth_nodes.empty()) {
      std::unordered_set<TreeNode*> next_depth_nodes;
      ++depth;
      for (auto node : same_depth_nodes) {
        if (node->left) {
          next_depth_nodes.insert(node->left);
        }
        if (node->right) {
          next_depth_nodes.insert(node->right);
        }
      }
      same_depth_nodes = std::move(next_depth_nodes);
    }
    return depth;
  }
};
```

---

別解

## step1-2.cpp

再帰でも書けるらしい。

- 右と左に訪れるのを繰り返す。
- 手作業的に考えると
  - 今自分はノードの上に立っていて、
  - 自分の次には、右側の人と左側の人がいる。
  - 2人に、立っている場所の深さを教えてあげる。つまり自分の深さ+1
  - どこまで深く行けたのか教えてもらう。
  - 2人のうち大きい方を自分の知っている最大の深さとして、上に報告する。
  - 行き止まりなら、深さを1つ減らして報告する

```cpp
class Solution {
 public:
  int maxDepth(TreeNode* root) { return MaxDepthHelper(root, 1); }

 private:
  int MaxDepthHelper(TreeNode* node, int depth) {
    if (!node) {
      return depth - 1;
    }
    int left_max_depth = MaxDepthHelper(node->left, depth + 1);
    int right_max_depth = MaxDepthHelper(node->right, depth + 1);
    return std::max(left_max_depth, right_max_depth);
  }
};
```


## step1-3.cpp

- さきほどの再帰の書き方はちょっと直感的でない気もする。
- 最後まで探索して、どれだけの深さ探索できたのか部下に教えてもらうほうがいいと思う。
  - まず自分が2人の部下に探索するように命ずる。
  - 部下は上司にどこまで探索できたのかを報告する。
  - 上司は報告を受けたうち、より深く探索できた方+1(自分の探索した場所)をさらに上の上司に報告する。
  - 命令する部下がいない場合は自分の立っている場所しか探索できなかったことになるので、その旨を上司に報告する。

```cpp
class Solution {
 public:
  int maxDepth(TreeNode* root) {
    if (!root) {
      return 0;
    }
    return MaxReachedDepth(root);
  }

 private:
  int MaxReachedDepth(TreeNode* node) {
    if (!node->left && !node->right) {
      return 1;
    }
    int left_max_depth = 0;
    int right_max_depth = 0;
    if (node->left) {
      left_max_depth = MaxReachedDepth(node->left);
    }
    if (node->right) {
      right_max_depth = MaxReachedDepth(node->right);
    }
    return 1 + std::max(left_max_depth, right_max_depth);
  }
};
```

- 計算量に関して
  - 時間計算量O(N)
  - 空間計算量O(N)
    - 関数がスタックに積まれる
    - 最大ノードが1万個あるけれど、これはスタックに全て積まれても大丈夫？
      - leftのみに１万個すべてつながっている場合は深さも1万になってその分積み上がる。
    - スタックの大きさがどれくらいあって、どれくらい積まれるとオーバーフローするのかがわからなかった。
    - 実験のために引数はほとんどコードを同じにして、無限にcountを増やしていくだけのプログラムをLeetCode上で動かした結果
      約1万回程度でTLEした。でもこれもあくまでもLeetCode上の話。
    - コメント集にあった。
      LeetCodeは再帰の回数は55000に設定されているとあった。さきほどのTLEとはまた違う数字だとは思う。
      ただ、環境依存はよくないので、どうしようか。



# コメント集を読む

- よくわからん解法を見つけた
  https://github.com/sakupan102/arai60-practice/blob/bbb45e773b7665b7bb6fc815f690ca9c0d15348c/arai60-104/solution.md

- stack + loop
```py
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        if not root: 
            return 0
        stack = [("go", (root, None, [None], [None], [None]))] # (node, direction, depth, left_depth, right_depth)
        while stack:
            go_back_flag, args = stack.pop()
            if go_back_flag == "go":
                node, direction, depth_ref, left_depth_ref, right_depth_ref = args
                if not node:
                    depth_ref[0] = 0
                    continue
                stack.append(("back", args))
                stack.append(("go", (node.left, "left", left_depth_ref,[None], [None])))
                stack.append(("go", (node.right, "right", right_depth_ref, [None], [None])))
            if go_back_flag == "back":
                node, direction, depth_ref, left_depth_ref, right_depth_ref = args
                depth_ref[0] = max(left_depth_ref[0], right_depth_ref[0]) + 1
                if not direction:
                    return depth_ref[0]
```

- これはおそらく、命令とその情報をstackに格納しているのか？
  1. back
  2. left(or right)
  2. right(or left)
  というappendの順番も大事な気がする。backのほうが先に格納してある必要がある。goが解決されたら戻るから。
- backするときにdepthを+1する感じか。
- たぶん*depth_ref系の変数が、配列を活かしている。mutableなオブジェクトの活用という説明があった。
  - depth_ref, left_depth_ref, right_depth_refは1回だけ生成される。ミュータブル参照で渡し続ける。
- directionがなくても、if (node == root) ならreturnでもいいと思う。directionは一行のために使っていて、rootかどうかを判断している。
- ちょっと理解しづらかった。また後で。



# step2

- step1-3.cppの解き方を採用する。
- 再帰の回数の問題は解決できていないが、進める。
- ほぼ変更はなしで、ヘルパー関数の名前のみ変更した。
  - 実際の現在いる深さを表したいのではなくて、部下が到達可能な、探索可能な深さを表したかった。
  - 今回は、MaxReacheableDepthの引数のnodeはnullptrでないことが前提なので、その旨をどのようにしたら
    ソースコードに示せるのかわからなかった。
  - とりあえずコメントとして残しておく。なにかいい方法はないか。


```cpp
class Solution {
 public:
  int maxDepth(TreeNode* root) {
    if (!root) {
      return 0;
    }
    return MaxReachableDepth(root);
  }

 private:
  // `node` should exits, mustn't nullptr
  int MaxReachableDepth(TreeNode* node) {
    if (!node->left && !node->right) {
      return 1;
    }
    int left_max_depth = 0;
    int right_max_depth = 0;
    if (node->left) {
      left_max_depth = MaxReachableDepth(node->left);
    }
    if (node->right) {
      right_max_depth = MaxReachableDepth(node->right);
    }
    return 1 + std::max(left_max_depth, right_max_depth);
  }
};

```

# step3

1. 2分40秒
2. 2分20秒
3. 2分8秒
