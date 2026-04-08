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
#include <queue>
#include <vector>
class Solution {
 public:
  TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
    std::deque<int> preorder_deque(preorder.begin(), preorder.end());
    std::queue<int> preorder_store(std::move(preorder_deque));
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
