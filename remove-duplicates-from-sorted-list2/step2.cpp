struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  // this method doesn't free the nodes unlinked by it;
  ListNode* deleteDuplicates(ListNode* head) {
    ListNode* dummy = new ListNode(0, head);
    ListNode* previous = dummy;
    ListNode* current = head;
    bool is_deleting = false;
    int deleting_number = 0;
    while (current) {
      if (is_deleting && deleting_number == current->val) {
        previous->next = current->next;
      } else if (!current->next || current->val != current->next->val) {
        is_deleting = false;
        previous = current;
      } else {
        is_deleting = true;
        deleting_number = current->val;
        previous->next = current->next;
      }
      current = current->next;
    }

    return dummy->next;
  }
};