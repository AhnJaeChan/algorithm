#include <iostream>
#include <string>
#include <vector>

using namespace std;

void removeZero(string &str);

void divideAndPrintCheck(string &N, int case_id);

int main() {
    int T;
    string N;

    cin >> T;

    for (int i = 1; i <= T; ++i) {
        cin >> N;

        divideAndPrintCheck(N, i);
    }

    return 0;
}

void removeZero(string &str) {
    string::size_type i = 0;
    while (str[i] == '0')
        i++;

    str.erase(0, i);
}

void divideAndPrintCheck(string &N, int case_id) {
    vector<char> A;
    vector<char> B;

    for (auto iter = N.crbegin(); iter != N.crend(); ++iter) {
        if (*iter == '4') {
            A.push_back('3');
            B.push_back('1');
        } else {
            A.push_back(*iter);
            B.push_back('0');
        }
    }

    string result_A(A.crbegin(), A.crend());
    string result_B(B.crbegin(), B.crend());

    removeZero(result_B);

    cout << "Case #" << case_id << ": " << result_A << " " << result_B << endl;
}
