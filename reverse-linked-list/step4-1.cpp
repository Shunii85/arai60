#include <utility>
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 private:
  std::pair<ListNode*, ListNode*> reverseListHelper(ListNode* node) {
    if (!node->next) {
      return {node, node};
    }
    auto [reversed_head, reversed_tail] = reverseListHelper(node->next);
    reversed_tail->next = node;
    node->next = nullptr;
    return {reversed_head, node};
  }

 public:
  ListNode* reverseList(ListNode* head) {
    if (!head) {
      return head;
    }
    auto [reversed_head, _] = reverseListHelper(head);
    return reversed_head;
  }
};
