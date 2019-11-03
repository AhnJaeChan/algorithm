#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
  // Returns the left position of the key to be inserted.
  // Ex) nums: {1, 3, 5, 7, 9}
  // key: 0, return: -1
  // key: 3, return: 1
  // key: 6, return: 2
  // key: 10, return: 4
  int binarySearch(vector<int> &nums, int left, int right, int key) {
    while (left <= right) {
      int mid = (left + right) / 2;
      if (nums[mid] < key) {
        left = mid + 1;
      } else if (nums[mid] > key) {
        right = mid - 1;
      } else {
        return mid;
      }
    }
    return right;
  }

  double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
    if (nums1.size() > nums2.size()) {
      swap(nums1, nums2);
    }
    int m = nums1.size(), n = nums2.size();

    int mid = (m + n) / 2;

    int l1 = 0, r1 = m - 1;
    int l2 = 0, r2 = n - 1;
    int i = m / 2;
    int j;

    while (i + j != mid) {
      i = (l1 + r1) / 2;
      j = binarySearch(nums2, l2, r2, nums1[i]);
      if (i + j < mid) {
        l1 = i + 1;
        l2 = j + 1;
      } else if (i + j > mid) {
        r1 = i - 1;
        r2 = j - 1;
      } else {
        break;
      }
    }

    return 0.0;
  }
};

int main() {
  Solution solution;

  vector<int> nums1 = {1, 3, 5, 7, 9};

  cout << solution.binarySearch(nums1, 0, nums1.size() - 1, 9) << endl;

  return 0;
}