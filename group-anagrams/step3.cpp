#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
 public:
  vector<vector<string>> groupAnagrams(const vector<string>& strs) {
    unordered_map<string, vector<int>> sorted_to_indices;
    for (int strs_i = 0; strs_i < strs.size(); ++strs_i) {
      string sorted_str = strs[strs_i];
      sort(sorted_str.begin(), sorted_str.end());
      sorted_to_indices[sorted_str].push_back(strs_i);
    }
    vector<vector<string>> grouped;
    for (auto& [_, indices] : sorted_to_indices) {
      vector<string> same_anagrams;
      for (int index : indices) {
        same_anagrams.push_back(strs[index]);
      }
      grouped.push_back(move(same_anagrams));
    }
    return grouped;
  }
};