#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
class WordManager {
 public:
  WordManager(std::string begin_word, std::vector<std::string> word_list) {
    word_list.push_back(begin_word);
    for (auto& word : word_list) {
      for (auto& created_pattern : ToPatterns(word)) {
        pattern_to_words[created_pattern].push_back(word);
      }
    }
  }
  std::vector<std::string> GetNeighbors(const std::string& word) {
    std::vector<std::string> neighbors;
    for (auto& matched_patterns : ToPatterns(word)) {
      for (auto& neighbor : pattern_to_words[matched_patterns]) {
        neighbors.push_back(neighbor);
      }
    }
    return neighbors;
  }

 private:
  std::unordered_map<std::string, std::vector<std::string>> pattern_to_words;
  std::vector<std::string> ToPatterns(const std::string& word) {
    std::vector<std::string> patterns;
    for (int i = 0; i < word.length(); ++i) {
      std::string pattern = word;
      pattern[i] = '*';
      patterns.push_back(std::move(pattern));
    }
    return patterns;
  }
};
class Solution {
 public:
  int ladderLength(std::string beginWord, std::string endWord,
                   std::vector<std::string>& wordList) {
    WordManager word_manager(beginWord, wordList);
    std::unordered_set<std::string> frontier_words{beginWord};
    std::unordered_set<std::string> visited{beginWord};
    int ladder_length = 1;
    while (!frontier_words.empty()) {
      std::unordered_set<std::string> next_frontier_words;
      for (const auto& word : frontier_words) {
        for (auto& neighbor : word_manager.GetNeighbors(word)) {
          if (neighbor == endWord) {
            return ladder_length + 1;
          }
          if (visited.contains(neighbor)) {
            continue;
          }
          next_frontier_words.insert(neighbor);
          visited.insert(neighbor);
        }
      }
      frontier_words = std::move(next_frontier_words);
      ++ladder_length;
    }
    return 0;
  }
};