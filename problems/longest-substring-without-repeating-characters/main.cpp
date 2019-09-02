#include <iostream>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    unordered_set<char> hs;

    int front = 0;
    size_t max_length = 0;

    for (char &c: s) {
      while (hs.find(c) != hs.end()) {
        hs.erase(s[front++]);
      }
      hs.insert(c);
      max_length = max(max_length, hs.size());
    }

    return max_length;
  }
};

int main() {
  Solution solution;

  string s = "abcdefg";

  cout << solution.lengthOfLongestSubstring(s) << endl;

  return 0;
}