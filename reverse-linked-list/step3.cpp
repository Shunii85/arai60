
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
    std::stack<ListNode*> warehouse;
    ListNode* node = head;
    ListNode* next = nullptr;
    ListNode* dummy = new ListNode(-1);
    while (node) {
      next = node->next;
      node->next = nullptr;
      warehouse.push(node);
      node = next;
    }
    node = dummy;
    while (!warehouse.empty()) {
      node->next = warehouse.top();
      warehouse.pop();
      node = node->next;
    }
    return dummy->next;
  }
};