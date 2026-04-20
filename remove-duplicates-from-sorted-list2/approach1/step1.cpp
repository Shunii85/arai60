// ACしないプログラム
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
    ListNode* base_node = head;
    ListNode* neighbor_node1 = nullptr;
    ListNode* neighbor_node2 = nullptr;

    while (base_node) {
      neighbor_node1 = base_node->next;
      base_node->next = nullptr;

      while (neighbor_node1) {
        neighbor_node2 = neighbor_node1->next;
        if (neighbor_node2 && neighbor_node1->val == neighbor_node2->val) {
          // 手作業でした操作を書いたが、謎に２つ先のノードに更新している。
          neighbor_node1 = neighbor_node1->next->next;
          neighbor_node2 = neighbor_node1->next;
        } else {
          base_node->next = neighbor_node1;
          neighbor_node1 = neighbor_node1->next;
          neighbor_node2 = neighbor_node1->next;
          break;
        }
      }
    }

    return head;
  }
};