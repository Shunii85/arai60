
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

#include <deque>
#include <vector>
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
