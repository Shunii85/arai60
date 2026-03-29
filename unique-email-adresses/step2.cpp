#include <string>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  int numUniqueEmails(const std::vector<std::string>& emails) {
    std::unordered_set<std::string> unique_emails;
    for (std::string processing_email : emails) {
      int char_pos = 0;
      while (char_pos < processing_email.length()) {
        char c = processing_email[char_pos];
        if (c == '+') {
          int boundary_pos = processing_email.find('@');
          processing_email.erase(char_pos, boundary_pos - char_pos);
          continue;
        }
        if (c == '.') {
          processing_email.erase(char_pos, 1);
          continue;
        }
        if (c == '@') break;
        char_pos++;
      }
      unique_emails.insert(processing_email);
    }
    return unique_emails.size();
  }
};