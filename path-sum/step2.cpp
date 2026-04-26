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
  bool HasPathSumHelper(TreeNode* node, int parent_sum, int target_sum) {
    if (!node) {
      return false;
    }
    int sum = parent_sum + node->val;
    if (IsLeafNode(node) && sum == target_sum) {
      return true;
    }
    return HasPathSumHelper(node->left, sum, target_sum)
           || HasPathSumHelper(node->right, sum, target_sum);
  }
  bool IsLeafNode(TreeNode* node) { return !node->left && !node->right; }
};
