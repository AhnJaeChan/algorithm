#include <iostream>
#include <string>

using namespace std;

class Solution {
private:
  int start = 0;
  int maxLength = 0;

public:
  void findPalindrome(string &s, int left, int right) {
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
      left--;
      right++;
    }

    if (maxLength < right - left - 1) {
      start = left + 1;
      maxLength = right - start;
    }
  }

  string longestPalindrome(string s) {
    int length = s.size();
    if (length < 2) {
      return s;
    }

    for (int i = 0; i < length - 1; i++) {
      findPalindrome(s, i, i);
      findPalindrome(s, i, i + 1);
    }

    return s.substr(start, maxLength);
  }
};

int main() {
  Solution solution;
  std::cout << solution.longestPalindrome("abcbd") << std::endl;
  return 0;
}