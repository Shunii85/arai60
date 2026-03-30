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