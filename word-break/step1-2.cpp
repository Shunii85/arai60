#include <queue>
#include <string>
#include <unordered_set>
#include <vector>
class Solution {
 public:
  bool wordBreak(const std::string s,
                 const std::vector<std::string>& word_dict) {
    std::unordered_set<std::string> word_set(word_dict.begin(),
                                             word_dict.end());
    std::vector<int> position_reached(s.length(), false);
    std::queue<int> start_positions({0});

    while (!start_positions.empty()) {
      int start = start_positions.front();
      start_positions.pop();

      if (start == s.length()) {
        return true;
      }

      std::string substring = "";
      for (int end = start; end < s.length(); ++end) {
        substring.push_back(s[end]);
        if (position_reached[end]) {
          continue;
        }
        if (word_set.contains(substring)) {
          position_reached[end] = true;
          start_positions.push(end + 1);
        }
      }
    }

    return false;
  }
};
