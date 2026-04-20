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
#include <unordered_map>
#include <vector>
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
