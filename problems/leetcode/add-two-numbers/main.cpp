#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *cur = new ListNode(0);
        ListNode *result = cur;

        int overflow = 0;

        while (l1 != NULL || l2 != NULL || overflow != 0) {
            int sum = getDigitValue(l1) + getDigitValue(l2) + overflow;

            overflow = getOverflow(sum);

            int digit = isOverflow(overflow) ? sum - 10 : sum;

            cur->next = new ListNode(digit);
            cur = cur->next;

            l1 = l1 != NULL ? l1->next : l1;
            l2 = l2 != NULL ? l2->next : l2;
        }

        return result;
    }

private:
    int getDigitValue(ListNode *l) {
        return l != NULL ? l->val : 0;
    }

    int getOverflow(int num) {
        return (num - 10) >= 0 ? 1 : 0;
    }

    bool isOverflow(int overflow) {
        return overflow == 1;
    }
};

int main() {
    ListNode list1[] = {ListNode(2), ListNode(4), ListNode(3)};
    ListNode list2[] = {ListNode(5), ListNode(6), ListNode(7)};

    list1[0].next = &list1[1];
    list1[1].next = &list1[2];

    list2[0].next = &list2[1];
    list2[1].next = &list2[2];

    Solution solution;

    solution.addTwoNumbers(list1, list2);

    return 0;
}