// 完成できなかったやつ
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
    ListNode* current = head;
    ListNode* next;

    while (current != nullptr) {
      while (next != nullptr && current->val == next->val) {
        current = current->next;
        next = current->next;

        current->next = next->next;
        next = current->next;
      }
    }

    return head;
  }
};