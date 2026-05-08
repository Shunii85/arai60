#include <string>
#include <vector>
class Solution {
 public:
  bool wordBreak(const std::string& s,
                 const std::vector<std::string>& word_dict) {
    std::vector<int> reachable(s.length(), false);

    for (int i = 0; i < s.length(); ++i) {
      for (const auto& word : word_dict) {
        if (reachable[i]) {
          continue;
        }
        int start = i - word.length() + 1;
        if (start < 0 || s[start] != word[0]) {
          continue;
        }
        if (start == 0 || reachable[start - 1]) {
          if (s.substr(start, word.length()) == word) {
            reachable[i] = true;
          }
        }
      }
    }

    return reachable[s.length() - 1];
  }
};
