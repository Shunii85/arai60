#include <unordered_set>
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  ListNode *detectCycle(ListNode *head){
    std::unordered_set<ListNode*> visited_nodes;
    ListNode* current = head;

    while(current != nullptr){
      bool visited = visited_nodes.contains(current);
      if(visited) {
        return current;
      } else {
        visited_nodes.insert(current);
      }
      current = current->next;
    }
    return nullptr;
  }
};