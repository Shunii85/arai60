// 間違えて深さ優先で実装していた。ACしていない
#include <list>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
class Solution {
 public:
  int ladderLength(std::string beginWord, std::string endWord,
                   std::vector<std::string>& wordList) {
    std::unordered_map<std::string, bool> visited;
    return FindShortestPath(beginWord, 1, endWord, wordList, visited);
  }

 private:
  // return the length of the shortest transformation path.
  int FindShortestPath(std::string word, int path_number, std::string endWord,
                       std::vector<std::string>& wordList,
                       std::unordered_map<std::string, bool>& visited) {
    if (word == endWord) {
      return path_number;
    }
    visited[word] = true;
    for (auto maybe_next_word : wordList) {
      if (!visited[maybe_next_word] && IsTransformable(word, maybe_next_word)) {
        return FindShortestPath(maybe_next_word, path_number + 1, endWord,
                                wordList, visited);
      }
    }
    return 0;
  }
  bool IsTransformable(std::string& before_str, std::string& after_str) {
    if (before_str.length() != after_str.length()) {
      return false;
    }
    int different_char_num = 0;
    for (int str_index = 0; str_index < before_str.length(); ++str_index) {
      if (before_str[str_index] != after_str[str_index]) {
        ++different_char_num;
      }
      if (different_char_num > 1) {
        return false;
      }
    }
    return different_char_num == 1;
  };
};
