#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
 public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
    if (k == nums.size()) return nums;
    unordered_map<int, int> inventory;
    for (int element : nums) {
      inventory[element] += 1;
    }
    auto comp = [&inventory](int n1, int n2) {
      return inventory[n1] > inventory[n2];
    };
    priority_queue<int, vector<int>, decltype(comp)> heap(comp);
    for (pair<int, int> ele_pair : inventory) {
      heap.push(ele_pair.first);
      if (heap.size() > k) heap.pop();
    }
    vector<int> k_tops;
    while (!heap.empty()) {
      k_tops.emplace_back(heap.top());
      heap.pop();
    }
    return k_tops;
  }
};