// コメントしながら修正していた。
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
    while (current != nullptr) {
      // ここが怪しかった。
      // 初期化しないと、2個目のwhileでこける, currentがあることをここで保証
      ListNode* next = current->next;
      while (next != nullptr && current->val == next->val) {
        // currentを前に進める必要はない。
        // current = current->next;
        // nextは最初に初期化したから下も必要ない
        // next = current->next;

        // 繋げなおすのはあとでいい。なぜなら、繋げなおすのは重複なものでないとわかったときのノードで良いから。
        // current->next = next->next;
        // これは必要ない、whileの最後の行でnextの更新はできている。
        // next = current->next;

        next = next->next;
      }
      // 重複した場合としなかった場合をどう分けるか難しかった。

      current->next = next;
      current = current->next;
    }

    return head;
  }
};