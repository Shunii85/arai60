struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
private:
  ListNode* getCollisionNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
      fast = fast->next->next;
      slow = slow->next;
      if (fast == slow) {
        return fast;
      }
    }
    return nullptr;
  }
public:
  ListNode *detectCycle(ListNode *head){
    ListNode* from_collision = getCollisionNode(head);
    if(!from_collision) {
      return nullptr;
    }
    ListNode* from_start = head;
    while (from_start != from_collision) {
      from_start = from_start->next;
      from_collision = from_collision->next;
    }
    return from_start;
  }
};