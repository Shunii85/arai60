#include <map>
#include <stack>
#include <string>

using namespace std;

// LeetCodeには上のプログラムは必要ない

class Solution {
 public:
  bool isValid(string s) {
    std::stack<char> open_brackets;
    std::map<char, char> match_closed_brackets{
        {'(', ')'},
        {'{', '}'},
        {'[', ']'},
    };
    for (char parenthesis : s) {
      switch (parenthesis) {
        case '(':
        case '{':
        case '[':
          open_brackets.push(parenthesis);
          break;
        case ')':
        case '}':
        case ']':
          if (open_brackets.empty()
              || match_closed_brackets[open_brackets.top()] != parenthesis) {
            return false;
          }
          open_brackets.pop();
          break;
        default:
          return false;
      }
    }
    return open_brackets.empty();
  }
};
