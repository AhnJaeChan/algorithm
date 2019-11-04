#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  string convert(string s, int numRows) {
    if (numRows >= s.size() || numRows == 1) {
      return s;
    }

    vector<char> results[numRows];
    bool down = true;
    int cnt = 0;
    int curRow = 0;
    while (cnt < s.size()) {
      results[curRow].push_back(s[cnt++]);
      if (down) {
        if (curRow == numRows - 1) {
          down = false;
          curRow--;
        } else {
          curRow++;
        }
      } else {
        if (curRow == 0) {
          down = true;
          curRow++;
        } else {
          curRow--;
        }
      }
    }

    string result(results[0].begin(), results[0].end());
    for (int i = 1; i < numRows; i++) {
      result += string(results[i].begin(), results[i].end());
    }

    return result;
  }
};

int main() {
  Solution solution;

  cout << solution.convert("abcd", 3) << endl;

  return 0;
}