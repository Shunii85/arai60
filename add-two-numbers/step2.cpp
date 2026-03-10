struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* result = new ListNode(-1);
    ListNode* tail = result;
    ListNode* digit1 = l1;
    ListNode* digit2 = l2;
    int sum = 0;
    int carry = 0;
    while (digit1 || digit2 || carry) {
      sum = carry;
      if (digit1) {
        sum += digit1->val;
        digit1 = digit1->next;
      }
      if (digit2) {
        sum += digit2->val;
        digit2 = digit2->next;
      }
      int val = sum % 10;
      carry = sum / 10;
      tail->next = new ListNode(val);
      tail = tail->next;
    }
    return result->next;
  }
};