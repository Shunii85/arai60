#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
class WordManager {
 public:
  WordManager(std::string begin_word, std::vector<std::string> word_list)
      : visited({begin_word}) {
    word_list.push_back(begin_word);
    for (const auto& word : word_list) {
      for (auto pattern : WordToPatterns(word)) {
        pattern_to_words[pattern].push_back(word);
      }
    }
  }
  std::vector<std::string> GetNeighbors(std::string word) {
    std::vector<std::string> neighbors;
    for (auto& matched_pattern : WordToPatterns(word)) {
      for (auto& neighbor : pattern_to_words[matched_pattern]) {
        if (visited.contains(neighbor)) {
          continue;
        }
        neighbors.push_back(neighbor);
        visited.insert(neighbor);
      }
    }
    return std::move(neighbors);
  }

 private:
  std::unordered_map<std::string, std::vector<std::string>> pattern_to_words;
  std::unordered_set<std::string> visited;
  std::vector<std::string> WordToPatterns(const std::string& word) {
    std::vector<std::string> patterns;
    for (int i = 0; i < word.size(); ++i) {
      std::string pattern = word;
      pattern[i] = '*';
      patterns.push_back(pattern);
    }
    return std::move(patterns);
  }
};
class Solution {
 public:
  int ladderLength(std::string beginWord, std::string endWord,
                   std::vector<std::string> wordList) {
    WordManager word_manager(beginWord, wordList);
    std::unordered_set<std::string> frontier_words{beginWord};
    int ladder_length = 1;
    while (!frontier_words.empty()) {
      std::unordered_set<std::string> next_frontiers;
      for (auto word : frontier_words) {
        for (auto neighbor : word_manager.GetNeighbors(word)) {
          if (neighbor == endWord) {
            return ladder_length + 1;
          }
          next_frontiers.insert(neighbor);
        }
      }
      frontier_words = std::move(next_frontiers);
      ++ladder_length;
    }
    return 0;
  }
};
