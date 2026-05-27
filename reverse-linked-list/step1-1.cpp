#include <stack>
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};
class Solution {
 public:
  ListNode* reverseList(ListNode* head) {
    if (!head) return head;
    std::stack<ListNode*> warehouse;
    ListNode* node = head;
    ListNode* dummy = new ListNode(-1);
    while (node) {
      warehouse.push(node);
      node = node->next;
    }
    node = dummy;
    while (!warehouse.empty()) {
      node->next = warehouse.top();
      warehouse.pop();
      node = node->next;
    }
    node->next = nullptr;
    return dummy->next;
  }
};