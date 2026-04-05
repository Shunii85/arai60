# step1

## 解法1

- 左の子、親、右の子で比べればいい。
  - 再帰的に比べればいい。

```cpp
// ACできていない
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

#include <limits>
class Solution {
 public:
  bool isValidBST(TreeNode* node) {
    if (!node) {
      return true;
    }
    int left_child_value = std::numeric_limits<int>::min();
    int right_child_value = std::numeric_limits<int>::max();
    if (node->left) {
      left_child_value = node->left->val;
    }
    if (node->right) {
      right_child_value = node->right->val;
    }
    if (!(left_child_value < node->val && node->val < right_child_value)) {
      return false;
    }
    return isValidBST(node->left) && isValidBST(node->right);
  }
};


- というふうに考えて実装してみたけど、単純に親子だけで比べたら良いわけではなさそうだった。
  - nodeの左側の部分木は、nodeより小さい値を持たなければいけない。
  - nodeの右側の部分木は、nodeより大きい値を持たなければいけない。

- 上司は部下に情報を与えて、それをもとに自分が正しい位置にいるのかを確認する、というやり方に変えよう。
  - 必要な情報は何だろうか
    - 小さい値と大きい値、つまり下限と上限が必要だ。
  - 部下に渡したい情報は何だろうか。
    - 上限と下限の数字が与えられる。
    - その範囲内に自分がいたとしよう。
      - 自分が上司の左の部下なら、上限を自分の値に更新する。
      - 自分が上司の右の部下なら、下限を自分の値に更新する。
  - といった具合だろうか。
  - 部下にいくときに、それより下の部下の持っている数字が存在していいかは更新されていく。
    - 左の部下にいくとき、条件を満たしていれば当然、存在できる部下の数字の上限は小さくなってしまうだろう。
    - 右の部下にいくとき、条件を満たしていれば当然、存在できる部下の数字の下限は大きくなってしまうだろう。

- 今度はオーバーフローしてしまうコードが出来上がった。

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

#include <limits>
class Solution {
 public:
  bool isValidBST(TreeNode* root) {
    return IsValidBSTHelper(root, std::numeric_limits<int>::min(),
                            std::numeric_limits<int>::max());
  }

 private:
  bool IsValidBSTHelper(TreeNode* node, int min_value, int max_value) {
    if (!node) {
      return true;
    }
    if (!(min_value <= node->val && node->val <= max_value)) {
      return false;
    }
    return IsValidBSTHelper(node->left, min_value, node->val - 1)
           && IsValidBSTHelper(node->right, node->val + 1, max_value);
  }
};

```

- geminiに相談して、min_valueとmax_value、要するに上限と下限を値ではなく、min_node/max_nodeというノードで保持しようということになった。
  - こうすることで、比べる相手がいない場合(nullptr)の場合は下限もしくは上限は存在しないことになるし、ノードの値はintで保証されているとすれば、それ以上の数字を境界に使う必要はない。


```cpp
class Solution {
 public:
  bool isValidBST(TreeNode* root) {
    return IsValidBSTHelper(root, nullptr, nullptr);
  }

 private:
  bool IsValidBSTHelper(TreeNode* node, TreeNode* min_node,
                        TreeNode* max_node) {
    if (!node) {
      return true;
    }
    if (min_node && node->val <= min_node->val) {
      return false;
    }
    if (max_node && node->val >= max_node->val) {
      return false;
    }
    return IsValidBSTHelper(node->left, min_node, node)
           && IsValidBSTHelper(node->right, node, max_node);
  }
};
```

- でも当然これって、valueでよくない?と思うけど、これ以前に、valueを境界線に使っていて、だけどintの最小もしくは最大の値を
rootに持ってこられたときに、その範囲チェックが正しく行えない。intの最小/最大の範囲をrootの範囲チェックに最初使うから。

## 他のコード

### LeetCodeの答え

- long型を使っていた
  - まぁって感じ
  - というかlongってintと同じではないの？？
    - リファレンス見る感じ、環境依存らしい。
      - https://en.cppreference.com/w/cpp/language/types.html
    - よって、long long使うのが確実かな
  - てかint型 => long型へのキャストは暗黙的に行われる？大丈夫なのはわかるけれど。

```cpp
class Solution {
 public:
 // numericのやつを使いたい
  bool isValidBST(TreeNode* root) { return valid(root, LONG_MIN, LONG_MAX); }

 private:
 // long longのがいいな
  bool valid(TreeNode* node, long minimum, long maximum) {
    if (!node) return true;

    if (!(node->val > minimum && node->val < maximum)) return false;

    return valid(node->left, minimum, node->val)
           && valid(node->right, node->val, maximum);
  }
};
```

- なんとなく、しっくりこない。
  - geminiに提案してもらったやつのほうが好きな気もする。
  - 足りないならデータ型を拡張してどうにかするというのは、気に入らないな。
    - もっと大きい範囲の数を扱いたいときのことを考えると、良くない解決方法だと思う。


# step2

- ほとんど変更なし。
  - ヘルパー関数の名前

```cpp
class Solution {
 public:
  bool isValidBST(TreeNode* root) { return valid(root, nullptr, nullptr); }

 private:
  bool valid(TreeNode* node, TreeNode* min_node, TreeNode* max_node) {
    if (!node) {
      return true;
    }
    if (min_node && node->val <= min_node->val) {
      return false;
    }
    if (max_node && node->val >= max_node->val) {
      return false;
    }
    return valid(node->left, min_node, node)
           && valid(node->right, node, max_node);
  }
};

```

## コメント集

- inorderでソートしてする方法もあるらしい
  - https://github.com/YukiMichishita/LeetCode/pull/8/changes#diff-4715b26790b92230b162cee20ac77591864a09b081158d7e9d0def2dc4ce5dc7R40-R100
  - 後で実装してみよう

# step3

1. 2分52秒
2. 2分
3. 1分45秒
4. 1分39秒 <= ここでさらにしっくりこれた感じする。

