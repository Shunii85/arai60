#include <string>
#include <unordered_map>
class Solution {
 public:
  int firstUniqChar(const std::string& s) {
    std::unordered_map<char, int> char_to_count;
    for (char c : s) {
      ++char_to_count[c];
    }
    for (int char_i = 0; char_i < s.length(); ++char_i) {
      if (char_to_count[s[char_i]] == 1) {
        return char_i;
      }
    }
    return -1;
  }
};