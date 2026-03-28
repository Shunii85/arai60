// LeetCode解答写し
#include <string>
#include <unordered_set>
#include <vector>
class Solution {
 public:
  int ladderLength(std::string beginWord, std::string endWord,
                   std::vector<std::string>& wordList) {
    std::unordered_set<std::string> word_set(wordList.begin(), wordList.end());
    if (word_set.find(endWord) == word_set.end()) {
      return 0;
    }
    std::unordered_set<std::string> begin_set{beginWord};
    std::unordered_set<std::string> end_set{endWord};
    std::unordered_set<std::string> visited;
    int steps = 1;
    while (!begin_set.empty() && !end_set.empty()) {
      std::unordered_set<std::string> next_set;
      if (begin_set.size() > end_set.size()) {
        swap(begin_set, end_set);
      }
      for (auto word : begin_set) {
        for (int i = 0; i < word.size(); ++i) {
          char original = word[i];
          for (char c = 'a'; c <= 'z'; ++c) {
            if (c == original) {
              continue;
            }
            word[i] = c;
            if (end_set.count(word)) {
              return steps + 1;
            }
            if (!visited.count(word) && word_set.count(word)) {
              next_set.insert(word);
              visited.insert(word);
            }
          }
          word[i] = original;
        }
      }
      begin_set = std::move(next_set);
      ++steps;
    }
    return 0;
  }
};