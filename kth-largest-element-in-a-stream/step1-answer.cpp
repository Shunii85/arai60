#include <queue>
#include <vector>
using namespace std;

class KthLargest {
 private:
  int num;
  priority_queue<int, vector<int>, greater<int>> pq;

 public:
  KthLargest(int k, vector<int>& nums) : num(k) {
    for (auto& n : nums) {
      pq.push(n);
      if (pq.size() > num) pq.pop();
    }
  }

  int add(int val) {
    pq.push(val);
    if (pq.size() > num) pq.pop();
    return pq.top();
  }
};