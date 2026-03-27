// 最初に解いたときに参考にしたプログラム
// ただ写生しただけなので、step1, 2, 3のファイルは書き直した
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
    if (!head) return nullptr;

    ListNode* prev = head;
    ListNode* node = head;
    while (node) {
      if (prev->val == node->val) {
        node = node->next;
        prev->next = node;
        continue;
      }
      prev = prev->next;
    }
    return head;
  }
};
