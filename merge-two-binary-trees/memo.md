# step1

- 二分木を合併する。
  - 2つの二分木を重ねてみた時、
    - 重なったノード同士は数字を足し合わせて新しいノードとする
    - どちらかのノードがある時、そのノードを新しいノードとする
    - どちらもなければなし

## 解法1

うまい具体的な例が浮かばなかったけど、考えてみる。

- rootと、left、rightしか存在しない小さな二分木を考えてみる。
  - root同士をみて、処理する。新しいRootを作る。
  - leftをみる。
    - ノードが2つともあるなら足し合わせてRootに刺す。
    - そうでなければ、どちらかをRootにさす。
  - rightをみる。leftと同様に。

- 各ノード人を立たせる例を使ってみる。
  - 今回は各ノードを担当する人が、root1, root2のどちらのbinary treeのノードの情報もスマホで見れるとする。
  - 各人の仕事内容
    - まず自分の担当するポジションを確認する。
    - 担当ポジションのノードを、2つそれぞれ確認する。
      - 2個あれば足し合わせて、ノードを作る。
      - 1個あれば、どちらかのノードを新しいノードとしてコピーする。
        (ここで仕事を終了することもできる。絶対この先はいかなくてもいい)
      - なければ仕事終了。即上のポジションの人に報告する。
    - 自分の左と右のポジションの人に仕事するように頼む。(要するに仕事をするポジションを教える)。

- 問題点としては、入力を書き換えている。
  - その旨をコメントに書いた。
    - というか普通にそうしなくても解けそうなので、書き直す。


### 入力を上書きしていた実装 ([step1-1.cpp](./step1-1.cpp))

```cpp
class Solution {
 public:
  // Warning: this function overwrite inputs.
  TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    if (!root1 && !root2) {
      return nullptr;
    }
    if (!root1) {
      return root2;
    }
    if (!root2) {
      return root1;
    }
    root1->val += root2->val;
    root1->left = mergeTrees(root1->left, root2->left);
    root1->right = mergeTrees(root1->right, root2->right);
    delete root2;
    return root1;
  }
};
```

### 入力を変更しないように書き直した実装 

- これなら、root1の方を書き換えなくて済む。
  - 新しく作った部分木を刺すようにしている。
  - どちらかのnodeがなかったら、root1かroot2を返しているけれど、これはroot1, root2の二分木の部分木を表しているだけであって、書き換えはしない。
    - でも今更書いていて思ったけれど、こちらのほうも危険ではないか？
      - 各ノードを開放しようとしたときに、**二重開放**する恐れがある。
      - 入力、出力ともに変更が双方向に影響する部分があるから、うーんという感じ

```cpp
class Solution {
 public:
  TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    if (!root1 && !root2) {
      return nullptr;
    }
    if (!root1) {
      return root2;
    }
    if (!root2) {
      return root1;
    }
    TreeNode* merged = new TreeNode(root1->val + root2->val);
    merged->left = mergeTrees(root1->left, root2->left);
    merged->right = mergeTrees(root1->right, root2->right);
    return merged;
  }
};
```

### 入力を消費するようにする実装

- こういう書き方もあり？

```cpp
class Solution {
 public:
 // Warning: Consumes inputs, and deallocates them;
  TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    if (!root1 && !root2) {
      return nullptr;
    }
    if (!root1) {
      return root2;
    }
    if (!root2) {
      return root1;
    }
    TreeNode* merged = new TreeNode(root1->val + root2->val);
    merged->left = mergeTrees(root1->left, root2->left);
    merged->right = mergeTrees(root1->right, root2->right);
    delete root1;
    delete root2;
    return merged;
  }
};
```

### 計算量

- 時間計算量、空間計算量ともにO(N)
  - 入力を書き換える場合は空間計算量O(1)


## コメント集を読む

- https://github.com/goto-untrapped/Arai60/pull/47/changes#diff-bc9f2e6a8912ca42541ca798434f0bec2d71fec372b62ce27ab0ab8bb0c444a1R41
  そういえば最初の条件文いらないな。root1がないときに、root2を返したとして、
  root2もnullptrならそれを返せばいい。

- https://discord.com/channels/1084280443945353267/1262688866326941718/1297934906189549599
  たしかにこれなら、いちいちどちらかのノードがなかった場合ダミーを作るということをしなくても済む。
  - left(), right(), val()というメソッドがいいな。
  - なぜダブルポインタである必要があるのか。
    - ダブルポインタをつくらないと、事前にleft, rightのノードを動的確保しておく必要があるのだろう。
      - nullptrを渡しても意味はない。
      - あとで動的確保したポインタを、ポインタ変数の参照(*ポインタ)に格納する。

  - 自分なりにC++でも書いてみよう。
    - [step1-2.cpp](./step1-2.cpp)

- https://github.com/colorbox/leetcode/pull/37#discussion_r1930699934
  番兵を一人用意しておいて、nullptrならそのアドレスをセットしておけばいい。番兵1人を使い回せる。


# step 2

- 最初の条件分は必要ないので消した。
- なぜか2つの重なるノードがあるときだけ新しいノードを作っていたので、それはなんだか変だなと思った。


```cpp
class Solution {
 public:
  TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    if (!root1 && !root2) {
      return nullptr;
    }
    if (!root1) {
      root1 = &dummy;
    }
    if (!root2) {
      root2 = &dummy;
    }
    auto merged = new TreeNode(root1->val + root2->val);
    merged->left = mergeTrees(root1->left, root2->left);
    merged->right = mergeTrees(root1->right, root2->right);
    return merged;
  }

 private:
  TreeNode dummy;
};
```

# step3

0. 40分程度
1. 2分13秒
2. 1分44秒

書き方変える。

1. 1分57秒
2. 1分40秒
3. 1分29秒
4. 1分30秒
