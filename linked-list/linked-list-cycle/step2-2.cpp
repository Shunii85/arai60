// こちらを採用する

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
        bool visited = visited_nodes.count(current) == 1;
        if(visited) {
          return true;
        } else {
          visited_nodes.insert(current);
        }
      }
      return false;
    }
};
