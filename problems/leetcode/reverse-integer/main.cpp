#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  int reverse(int x) {
    int result = 0;

    while (x != 0) {
      int digit = x % 10;

      if (result > INT32_MAX / 10 || (result == INT32_MAX / 10 && digit > 7)) {
        return 0;
      }

      if (result < INT32_MIN / 10 || (result == INT32_MIN / 10 && digit < -8)) {
        return 0;
      }

      result = result * 10 + digit;
      x /= 10;
    }

    return result;
  }
};

int main() {
  Solution solution;

  std::cout << solution.reverse(-123) << std::endl;

  return 0;
}