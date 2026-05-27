
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 private:
  ListNode* reverseListHelper(ListNode* node) {
    if (!node->next) {
      return node;
    }
    ListNode* reversed_head = reverseListHelper(node->next);
    ListNode* reversed_tail = node->next;
    reversed_tail->next = node;
    node->next = nullptr;
    return reversed_head;
  }

 public:
  ListNode* reverseList(ListNode* head) {
    if (!head) {
      return head;
    }
    return reverseListHelper(head);
  }
};
