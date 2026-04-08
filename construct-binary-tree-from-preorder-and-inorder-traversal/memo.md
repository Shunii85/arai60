# step1


- inorder, preorderでソートされた数の配列から、二分木(二分探索木ではない)を構築する問題
  - 二分木のorderとは？
    - inorder(中間順): 先に左の部分木を処理してから、そのノードを処理して、右側の処理をするという順番
      これは、ソートされたもの。
    - preorder(先行順): ノードを処理してから、左の部分木を処理し、右の部分木を処理する。

- 特徴としては、
  - inorderに関しては、ある数字を1つ選んでみた時、その時点でもうすでに左の部分木についてはtraversalが終わっている。
  - preorderに関しては、根の情報が左側優先で出てくる。ということ。
    - ただ、いつ左/右のノードなのかはわからない。

---

- ちょっとどうすればいいのか全然わからずに答えを見る。
  - 何となく理解はした。
  - preorderは、順に取り出していけば、rootから始まって、left => rightの優先順位で深さ優先探索を行ったような順にでてくる。
    - ひたすらなるべく左側のノードを取り出して、なければその右をとる。
  - inorderは、あるindexを選んだ時、[左, index, 右]というように並んでいる。
    - でも左にある値がすべて自分の左側の部分木であるとは限らない。ただし、うまくノードを消費できればその限りではない。

- 手順としては、
  1. preorderから先頭を取り出す。ノードを作る。
  2. それをもとに、inorderで、左側、右側に分ける。
  3.  左側について処理を行う。1.から。
  4. 右側について処理を行う。 1.から。

- なんか整理できて来た。sortedArrayToBSTでは、根の選び方が決まっていた。
  - その根を教えてくれるのが、preorderの役割かな。
    1. 根をピックする。
    2. 左と右でわける。
    3. また戻って、左側で部分木の根をピックする。
    4. 左と右で分ける。
    ...


- LeetCodeの答え
  - なぜかdequeが使われていて、queueでいいじゃないかと思ったのだけど、
  - 書き直してみると、vectorのpreorderからqueueをコピー生成するときに、コンストラクタの引数が一致しないと言われてしまった。
    - LeetCodeのジャッジシステムでは普通に通る。
    - なんでだ？C++のバージョン的にもできるはずだし。[fast, last)のコピー
  - そもそもqueueがコンテナではなく、コンテナアダプタだからなのか。なかのコンテナを初期化するようにイテレータは渡せないのか、、
    - https://en.cppreference.com/w/cpp/container/queue/queue.html
    - これの(6)じゃないのかなぁ..


```cpp
class Solution {
 public:
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    // queueでよくないか？前から消費するだけだから
    deque<int> preorderdeque(preorder.begin(), preorder.end());
    return build(preorderdeque, inorder);
  }

 private:
 // inorderはconstでいいな。iterator使わずにindexでもできそう？
  TreeNode* build(deque<int>& preorder, vector<int>& inorder) {
    if (!inorder.empty()) {
      int val = preorder.front();
      preorder.pop_front();
      auto it = find(inorder.begin(), inorder.end(), val);
      int idx = it - inorder.begin();

      TreeNode* root = new TreeNode(val);
      vector<int> leftInorder(inorder.begin(), inorder.begin() + idx);
      vector<int> rightInorder(inorder.begin() + idx + 1, inorder.end());

      root->left = build(preorder, leftInorder);
      root->right = build(preorder, rightInorder);

      return root;
    }

    return nullptr;
  }
};
```

- 時間計算量: O(N^2)
  - ノードが左もしくは右側の片方に一方向でつながったものになる場合(偏った木)、findの探索が線形時間になる。
    - n + (n-1) + (n - 2) + ...
- 空間計算量: O(N^2)
  - 時間計算量と同じく最悪のパターンを考えると、
    - n + (n-1) + (n - 2) + ...
    - という具合にleftInorder/rightInorderがコピーされていく。

- 理解した状態で、[step1-1.cpp](./step1.cpp)に書き直し。
  - 多少編集している。

```cpp
#include <queue>
#include <vector>
class Solution {
 public:
  TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
    std::queue<int> preorder_store(preorder.begin(), preorder.end());
    return build(preorder_store, inorder);
  }

 private:
  TreeNode* build(std::queue<int>& preorder, const std::vector<int>& inorder) {
    if (!inorder.empty() && !preorder.empty()) {
      int value = preorder.front();
      preorder.pop();
      auto it = std::find(inorder.begin(), inorder.end(), value);
      int index = it - inorder.begin();

      std::vector<int> left_inorder(inorder.begin(), inorder.begin() + index);
      std::vector<int> right_inorder(inorder.begin() + index + 1,
                                     inorder.end());
      return new TreeNode(value, build(preorder, left_inorder),
                          build(preorder, right_inorder));
    }
    return nullptr;
  }
};
```

---

- 書いていて思ったのが、毎回inorderをコピーしているのはもったいないなと思った。単純に範囲指定で良くない？と
  - で、時間計算量がＯ(N)にできる回答があって、これは値をキーとして、インデックスを格納するハッシュテーブルを使うとのこと。
  - 範囲指定なら、この解法が使える。毎回コピーしていたら、inorderが変わって、indexが変わってしまうから。
- LeetCodeの解答は以下の感じ

```cpp
class Solution {

private:
    int preorderIndex;
    // value_to_indexの方が好み。
    unordered_map<int, int> mapping;

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        mapping.clear();
        for (int i = 0; i < inorder.size(); i++) {
            mapping[inorder[i]] = i;
        }

        preorderIndex = 0;
        return build(preorder, 0, inorder.size() - 1);
    }

private:
    TreeNode* build(vector<int>& preorder, int start, int end) {
        if (start > end) return nullptr;
        // まぁ、こういうやり方もあるか。だけどqueueでも良かったと思う。
        int rootVal = preorder[preorderIndex++];
        TreeNode* root = new TreeNode(rootVal);
        int mid = mapping[rootVal];

        root->left = build(preorder, start, mid - 1);
        root->right = build(preorder, mid + 1, end);

        return root;
    }    
};
```

- こっちの書き方の方が好み。計算量とかではなく、範囲(start, end)で指定するのが。
- [step1-2.cpp](./step1-2.cpp)で書き直した。

```cpp
class Solution {
 public:
  TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
    std::unordered_map<int, int> value_to_index;
    for (int index = 0; index < inorder.size(); ++index) {
      value_to_index[inorder[index]] = index;
    }
    std::deque<int> preorder_store(preorder.begin(), preorder.end());
    return build(preorder_store, value_to_index, 0, inorder.size() - 1);
  }

 private:
  TreeNode* build(std::deque<int>& preorder_store,
                  std::unordered_map<int, int>& value_to_index, int start,
                  int end) {
    if (start > end) {
      return nullptr;
    }
    if (!preorder_store.empty()) {
      int value = preorder_store.front();
      preorder_store.pop_front();
      int index = value_to_index[value];
      return new TreeNode(
          value, build(preorder_store, value_to_index, start, index - 1),
          build(preorder_store, value_to_index, index + 1, end));
    }
    return nullptr;
  }
};
```

- value_to_indexに関しては、constにして、value_to_index[index]を、value_to_index.at(index)にしてもいいと思った。
  - 例外は投げられないと思うけれど、なんだか嫌だった。
  - assertを書いておく？ assert(value_to_index.contains(value));

# step2

step1-2.cppを採用。

