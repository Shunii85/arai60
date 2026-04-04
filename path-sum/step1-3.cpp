struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

#include <queue>
class Solution {
 public:
  bool hasPathSum(TreeNode* root, int targetSum) {
    if (!root) {
      return false;
    }
    std::queue<std::pair<TreeNode*, int>> node_and_sum({{root, root->val}});
    while (!node_and_sum.empty()) {
      auto [node, sum] = node_and_sum.front();
      node_and_sum.pop();
      if (IsLeafNode(node) && sum == targetSum) {
        return true;
      }
      if (node->left) {
        node_and_sum.push({node->left, sum + node->left->val});
      }
      if (node->right) {
        node_and_sum.push({node->right, sum + node->right->val});
      }
    }
    return false;
  }

 private:
  bool IsLeafNode(TreeNode* node) { return !node->left && !node->right; }
};
