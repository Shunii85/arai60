# step1

## 問題の概観

- 与えられた二分木の最小の深さを求める。
  - 最小の深さとは、根から最も近い葉へたどり着くように辿っていったときのノードの数。

## 解法1 ([step1-1.cpp](./step1-1.cpp))

- BFSで解けばいい
- 同じ深さのノードを扱うようにしたい。

- 実装したあとに気がついたけど、これって二分木が閉路を持たないから訪れられたかどうかの管理なしで考えられたな。
  - そもそも閉路持ってるグラフだと深さがなにか定義しづらいか？

- 時間計算量
  - O(N)
    - すべてのノードが1つの路としてつながっていたらこうなる。
- 空間計算量
  - O(N)
    - 完全二分木の場合が、深さが増えるごとに階層あたりのノードが最も多くなる
    - 深さはlogN程度
    - だいたい2^(logN)が同じ深さのノードの集合、レベルの大きさ
    - よってN程度

- 気になったこととして、葉に辿りつかなくて`same_depth_nodes`が空になる状況はないから、whileを抜けたあとの
返り値についてコメントで説明しておいたほうがいいのかな？と思った。

  どういうコメントがふさわしいのかわからなかった。


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
  int minDepth(TreeNode* root) {
    if (!root) {
      return 0;
    }
    std::vector<TreeNode*> same_depth_nodes{root};
    int depth = 0;
    while (!same_depth_nodes.empty()) {
      ++depth;
      std::vector<TreeNode*> next_depth_nodes;
      for (const auto& node : same_depth_nodes) {
        if (IsLeafNode(node)) {
          return depth;
        }
        if (node->left) {
          next_depth_nodes.push_back(node->left);
        }
        if (node->right) {
          next_depth_nodes.push_back(node->right);
        }
      }
      same_depth_nodes = std::move(next_depth_nodes);
    }
    return -1;
  }

 private:
  bool IsLeafNode(TreeNode* node) { return !node->left && !node->right; }
};
```

## 解法2 ([step1-2.cpp](./step1-2.cpp))

- DFSでとく。
  - stack
  - 再帰関数
- でも深さ優先探索の場合、min_depthを決定するには最後まで探索しないと決定できない。


```cpp
class Solution {
 public:
  int minDepth(TreeNode* root) {
    if (!root) {
      return 0;
    }
    return MinDepthHelper(root);
  }

 private:
  int MinDepthHelper(TreeNode* node) {
    if (!node->left && !node->right) {
      return 1;
    }
    int left_min_depth = INT_MAX;
    int right_min_depth = INT_MAX;
    if (node->left) {
      left_min_depth = MinDepthHelper(node->left);
    }
    if (node->right) {
      right_min_depth = MinDepthHelper(node->right);
    }
    return 1 + std::min(left_min_depth, right_min_depth);
  }
};
```

または

```cpp
class Solution {
 public:
  int minDepth(TreeNode* root) {
    if (!root) {
      return 0;
    }
    if (!root->left && !root->right) {
      return 1;
    }
    int left_min_depth = INT_MAX;
    int right_min_depth = INT_MAX;
    if (root->left) {
      left_min_depth = minDepth(root->left);
    }
    if (root->right) {
      right_min_depth = minDepth(root->right);
    }
    return 1 + std::min(left_min_depth, right_min_depth);
  }
};
```

- 最小を1にしたほうが自然な気がする。
  - return 0をどこかに入れて実装できるやり方あるのかな？

# step2

## 他のコードを読む

### Code1

- LeetCode上にあったコード。
- 解法1と同じ解き方をしているはずだけど、こちらのが早い様子。
  - vectorを使うと、次の深さのノードを管理するためのvectorを用意するために時間がかかっているのか？

- 感想
  - 確かにqueueを使っても、レベル(同じ深さのノードの集合を総称して呼ぶ)の数だけpopすればいいのか。わかりやすい。
  - depthは最初にインクリメントするほうが自分としてはわかりやすい
  - 最後に`return depth`しているけれど、あそこにたどり着くことはないと思う。

```cpp
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == nullptr) return 0;

        queue<TreeNode*> q;
        q.push(root);
        int depth = 1;

        while (!q.empty()) {
            int levelSize = q.size();

            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();

                if (node->left == nullptr && node->right == nullptr)
                    return depth;

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            depth++;
        }

        return depth;
    }
};
```

## コメント集

### Comment1

https://github.com/olsen-blue/Arai60/pull/22/changes/BASE..cab49361fcad464de73ee93282fc2e2743b8314a#r1925335296

> この depth の更新は while の一番下のほうが素直じゃないでしょうか。

- んーそう感じる人もいるのか。
- 自分にはこれからどの深さを処理するのかがわかりやすい。
  - でも今書いていて思ったけど、最初に深さを増やすというのもそれはそれで変だな。
  - 処理が終わったら次の深さに進むよ、というほうが自然か


## 整理する ([step2.cpp](./step2.cpp))

LeetCodeの解き方がわりと好みだったのでこれを整理しようと思う。

```cpp
class Solution {
 public:
  int minDepth(TreeNode* root) {
    if (!root) {
      return 0;
    }
    std::queue<TreeNode*> nodes({root});
    int depth = 1;
    while (!nodes.empty()) {
      int levelSize = nodes.size();
      for (int i = 0; i < levelSize; i++) {
        TreeNode* node = nodes.front();
        nodes.pop();
        if (IsLeafNode(node)) {
          return depth;
        }
        if (node->left) {
          nodes.push(node->left);
        }
        if (node->right) {
          nodes.push(node->right);
        }
      }
      ++depth;
    }
    return -1;
  }

 private:
  bool IsLeafNode(TreeNode* node) { return !node->left && !node->right; }
};
```

# step3

1. 3分2秒
2. 3分14秒
3. 