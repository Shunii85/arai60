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
    // 今注目したいノードだから、current, currで問題ないと思う
    ListNode* curr = head;

    while (curr) {
      ListNode* next = curr->next;
      while (next != nullptr && curr->val == next->val) {
        next = next->next;
      }
      // ここで繋ぎなおし
      curr->next = next;
      // 新しいvalを持つノードに移動。これを次に注目するノードとする
      curr = curr->next;
    }

    return head;
  }
};