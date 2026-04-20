struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* deleteDuplicates(ListNode* head) {
    ListNode* manager = new ListNode(-1, head);
    ListNode* last_resolved = manager;
    ListNode* curr = head;
    while (curr && curr->next) {
      if (curr->val == curr->next->val) {
        while (curr->next && curr->val == curr->next->val) {
          curr = curr->next;
        }
        last_resolved->next = curr->next;
      } else {
        last_resolved = curr;
      }
      curr = curr->next;
    }
    return manager->next;
  }
};