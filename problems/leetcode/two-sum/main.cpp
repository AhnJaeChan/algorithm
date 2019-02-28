#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        vector<int> result = {-1, -1};

        for (auto outer_it = nums.begin(); outer_it != nums.end() - 1; ++outer_it) {
            for (auto inner_it = outer_it + 1; inner_it != nums.end(); ++inner_it) {
                if (*outer_it + *inner_it == target) {
                    result[0] = (int) distance(nums.begin(), outer_it);
                    result[1] = (int) distance(nums.begin(), inner_it);
                    break;
                }
            }
        }

        return result;
    }
};

int main() {
    Solution solution;

    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    // For printing only
    for (auto i: solution.twoSum(nums, target)) {
        cout << i << endl;
    }

    return 0;
}
