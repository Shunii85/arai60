#include <queue>
#include <vector>
using namespace std;

class KthLargest {
 private:
  int k;
  priority_queue<int, vector<int>, greater<int>> scores;

 public:
  KthLargest(int k, vector<int>& nums) : k(k) {
    for (int& score : nums) {
      scores.push(score);
      if (scores.size() > k) scores.pop();
    }
  }

  int add(int val) {
    scores.push(val);
    if (scores.size() > k) scores.pop();
    return scores.top();
  }
};