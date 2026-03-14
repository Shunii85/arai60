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
    bool is_carry = false;
    while (digit1 || digit2 || is_carry) {
      int sum = 0;
      if (digit1) {
        sum += digit1->val;
        digit1 = digit1->next;
      }
      if (digit2) {
        sum += digit2->val;
        digit2 = digit2->next;
      }
      if (is_carry) sum++;
      if (sum >= 10) {
        is_carry = true;
        sum -= 10;
      } else {
        is_carry = false;
      }
      tail->next = new ListNode(sum);
      tail = tail->next;
    }
    return result->next;
  }
};