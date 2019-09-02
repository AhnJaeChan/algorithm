#include <iostream>
#include <string>
#include <vector>

using namespace std;

int euclideanGcd(int num1, int num2);

void decryptToPrimes(vector<int> &numbers);

int main() {
    int T, N;
    int num;
    vector<int>::size_type L;

    cin >> T;

    for (int i = 1; i <= T; ++i) {
        cin >> N >> L;

        vector<int> input_numbers;
        input_numbers.reserve(L);

        for (int j = 0; j < L; ++j) {
            cin >> num;
            input_numbers.push_back(num);
        }

        decryptToPrimes(input_numbers);
//        cout << "Case #" << i << ": " << findPath(P, N) << endl;
    }

    return 0;
}

int euclideanGcd(int num1, int num2) {
    if (num1 == 0) {
        return num2;
    }
    return euclideanGcd(num2 % num1, num1);
}

void decryptToPrimes(vector<int> &numbers) {
    auto iter = numbers.begin();

    while (*(iter + 1) == *iter++);

    int gcd = euclideanGcd(*iter, *(iter - 1));

    int front = *(iter - 1) / gcd;

    vector<int> decoded_primes;
    for (auto iter_front = numbers.begin(); iter_front != iter; iter++) {
        decoded_primes.push_back(front);
        decoded_primes.push_back(gcd);
    }

    for (; iter != numbers.end(); iter++) {
        gcd = decoded_primes.back();
        decoded_primes.push_back(gcd);
        decoded_primes.push_back(*iter / gcd);
    }
}