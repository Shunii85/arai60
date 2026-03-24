struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
      ListNode* slow_pointer = head;
      ListNode* fast_pointer = head;
      while (fast_pointer && fast_pointer->next) {
        slow_pointer = slow_pointer->next;
        fast_pointer = fast_pointer->next->next;
        if (slow_pointer == fast_pointer) {
          return true;
        }
      }
      return false;
    }
};