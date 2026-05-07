#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
    if (k == nums.size()) return nums;
    unordered_map<int, int> count_map;
    for (int n : nums) {
      count_map[n] += 1;
    }
    auto comp = [&count_map](int n1, int n2) {
      return count_map[n1] > count_map[n2];
    };
    priority_queue<int, vector<int>, decltype(comp)> heap(comp);
    for (pair<int, int> p : count_map) {
      heap.push(p.first);
      if (heap.size() > k) heap.pop();
    }
    vector<int> tops(k);
    for (int i = k - 1; i >= 0; i--) {
      tops.emplace_back(heap.top());
      heap.pop();
    }
    return tops;
  }
};