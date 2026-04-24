struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

#include <vector>
class Solution {
 public:
  std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    std::vector<std::vector<int>> level_grouped_values;
    GroupingByLevel(level_grouped_values, root, 1);
    return level_grouped_values;
  }

 private:
  void GroupingByLevel(std::vector<std::vector<int>>& grouped, TreeNode* node,
                       int level) {
    if (!node) return;
    while (grouped.size() < level) {
      grouped.push_back({});
    }
    grouped[level - 1].push_back(node->val);
    GroupingByLevel(grouped, node->left, level + 1);
    GroupingByLevel(grouped, node->right, level + 1);
  }
};
