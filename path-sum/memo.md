# step1

- 普通に探索していって、Leafならtargetと等しいかを考えればいいと思う。
- -1000 <= Node.val <= 1000より、targetより大きくなったら引き返すということもできない。

## 解法1 ([step1-1.cpp](./step1-1.cpp))

- DFSでたどっていく
  - Leafにたどり着いてかつtargetと同じなら、true.
- 最初に、IsLeafの判定を入れずに、nodeがnullptrならreturn sum == targetのように書いていたけど、それじゃLeafかどうかの判定が出来ないなと思った。


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
  bool hasPathSum(TreeNode* root, int targetSum) {
    return HasPathSumHelper(root, 0, targetSum);
  }

 private:
  bool HasPathSumHelper(TreeNode* node, int sum, int target_sum) {
    if (!node) {
      return false;
    }
    sum += node->val;
    if (IsLeafNode(node) && sum == target_sum) {
      return true;
    }
    return HasPathSumHelper(node->left, sum, target_sum)
           || HasPathSumHelper(node->right, sum, target_sum);
  }
  bool IsLeafNode(TreeNode* node) { return !node->left && !node->right; }
};
```

- 時間計算量: O(N)
  - 最悪すべてのLeafまでのPathを辿るように探索するから。
- 空間計算量: O(logN)
  - 最悪logN、二分木の高さの分程度スタックに関数が積みあがる。
  - 最大ノードの数5000個 => 高さ13くらい


### Iterativeに書いた

- stackを使ったDFS
  [step1-2.cpp](./step1-2.cpp)
- queueを使ったBFS
  [step1-3.cpp](./step1-3.cpp)

## 他の人のコードを読む。

- https://github.com/rossy0213/leetcode/pull/14/changes#diff-34efe727dd1ad18d2b320e1e34b81b9129b8d0af26c5e979c65907a7f3f23d3bR41-R55
  1. target_sumを更新していく方法。
    - 自分でも[step1-4.cpp](./step1-4.cpp)に書いてみた。
    - rootをnodeにした方がわかりやすいからそうする。呼び出し側からしたら同じだし。
  2. node->valを更新していく、そこまでのpathの和にするというのもあった。入力を変更するのは好みではないけど、すっきりかけるなと思った。

# step2

- [step1-1.cpp](./step1-1.cpp)を採用。
- ヘルパー関数の引数のsumが伝わりにくい、本来自分が伝えたい意味は
  - 親ノードまでのルートの和を受け取りたいので、parent_sumに変更。

# step3

1. 2分50秒
2. 2分40秒
3. 2分19秒
