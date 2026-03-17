// step1のほうが個人的にはわかりやすい。
#include <set>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
      std::set<ListNode*> visited_nodes;
      ListNode* current = head;

      while (current->next != nullptr) {
        bool visited = !visited_nodes.insert(current).second;
        if(visited) {
          return true;
        }
      }
      return false;
    }
};
