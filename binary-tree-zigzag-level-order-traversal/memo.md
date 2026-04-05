# step1

## 解法1 ([step1-1.cpp](./step1-1.cpp))

- BFSでいつもどおり辿っていく。
  - ただ、zigzag orderなので、ループ毎に、level orderのvalueの順番を変えたい。
    - 単純に、値を追加したあとに、フラグをもとにstd::reverseする。

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

#include <algorithm>
#include <vector>
class Solution {
 public:
  std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root) {
    if (!root) {
      return {};
    }
    std::vector<std::vector<int>> zigzag_level_order_values;
    std::vector<TreeNode*> current_level_nodes({root});
    bool from_right = false;
    while (!current_level_nodes.empty()) {
      std::vector<int> values;
      std::vector<TreeNode*> next_level_nodes;
      for (auto node : current_level_nodes) {
        values.push_back(node->val);
        if (node->left) {
          next_level_nodes.push_back(node->left);
        }
        if (node->right) {
          next_level_nodes.push_back(node->right);
        }
      }
      if (from_right) {
        std::reverse(values.begin(), values.end());
      }
      zigzag_level_order_values.push_back(std::move(values));
      current_level_nodes = std::move(next_level_nodes);
      from_right = !from_right;
    }
    return zigzag_level_order_values;
  }
};
```

- 時間計算量: O(N)
  - すべてのノードを辿るのにNステップ
  - reverseするのにもNステップ程度
  - 実行時間
- 空間計算量: O(N)
  - 平衡木のときに、levelのノード数が各深さで最大になる。
    - 深さlogN, その深さのレベル、N個程度

## 解法2 (LeetCodeの解答コピペ)

- 辿り方をzigzagにはできるか？
  - 追加の順番が二種類になる。
    - left ~> right
    - right ~> left

- dequeを使えばできるらしい。
  - LeetCodeの解答にあった。
  - 解答貼り付けるときは自分なりにコメントをしておくか。

```cpp
class Solution {
 public:
  vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if (!root) return res;

    deque<TreeNode*> dq;
    dq.push_back(root);
    // ちょっと動詞、関数みたい ?
    bool reverse = false;

    while (!dq.empty()) {
      // level_sizeかな
      int size = dq.size();
      vector<int> level;

      for (int i = 0; i < size; i++) {
        // ぶら下がりifやめたら、ネスト深くなりそう。
        // 関数に切り出すかな
        if (!reverse) {
          TreeNode* node = dq.front();
          dq.pop_front();
          level.push_back(node->val);
          // ぶらさがりifやだ
          if (node->left) dq.push_back(node->left);
          if (node->right) dq.push_back(node->right);
        } else {
          TreeNode* node = dq.back();
          dq.pop_back();
          level.push_back(node->val);
          if (node->right) dq.push_front(node->right);
          if (node->left) dq.push_front(node->left);
        }
      }

      // ムーブしたいね
      res.push_back(level);
      reverse = !reverse;
    }

    return res;
  }
};
```

- [step1-2.cpp](./step1-2.cpp)に書き直してみたけど、なんか長ったらしくて好きでない。

```cpp
class Solution {
 public:
  std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root) {
    if (!root) {
      return {};
    }
    std::vector<std::vector<int>> zigzag_level_order_values;
    std::deque<TreeNode*> frontier{root};
    bool from_right = false;
    while (!frontier.empty()) {
      int level_size = frontier.size();
      std::vector<int> values;
      for (int i = 0; i < level_size; ++i) {
        TreeNode* node;
        if (!from_right) {
          node = frontier.front();
          frontier.pop_front();
          if (node->left) {
            frontier.push_back(node->left);
          }
          if (node->right) {
            frontier.push_back(node->right);
          }
        } else {
          node = frontier.back();
          frontier.pop_back();
          if (node->right) {
            frontier.push_front(node->right);
          }
          if (node->left) {
            frontier.push_front(node->left);
          }
        }
        values.push_back(node->val);
      }
      zigzag_level_order_values.push_back(std::move(values));
      from_right = !from_right;
    }
    return zigzag_level_order_values;
  }
};

```

# step2

- どうでもよいけど、コメント集ゼロだった。特に何もないのか。

- 解法1を採用する。
  - ほぼ変更なし

# step3

1. 4分01秒
2. 3分45秒
3. 3分32秒
