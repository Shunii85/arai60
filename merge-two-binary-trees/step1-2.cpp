#include <stack>
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

struct SamePositionNodes {
  TreeNode* node1;
  TreeNode* node2;
  TreeNode** mergedNode;
};
class Solution {
 public:
  TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    TreeNode* merged;
    std::stack<SamePositionNodes> same_position_nodes;
    same_position_nodes.push({root1, root2, &merged});
    while (!same_position_nodes.empty()) {
      auto [node1, node2, mergedNode] = same_position_nodes.top();
      same_position_nodes.pop();
      if (!node1 && !node2) {
        continue;
      }
      *mergedNode = new TreeNode(value(node1) + value(node2));
      same_position_nodes.push(
          {left(node1), left(node2), &((*mergedNode)->left)});
      same_position_nodes.push(
          {right(node1), right(node2), &((*mergedNode)->right)});
    }
    return merged;
  }

 private:
  TreeNode* left(TreeNode* node) { return node ? node->left : nullptr; }
  TreeNode* right(TreeNode* node) { return node ? node->right : nullptr; }
  int value(TreeNode* node) { return node ? node->val : 0; }
};
