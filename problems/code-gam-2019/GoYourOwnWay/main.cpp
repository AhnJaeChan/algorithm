#include <iostream>
#include <string>

using namespace std;

string findPath(string &P, int N);

char invertPath(char path);

int main() {
    int T, N;
    string P;

    cin >> T;

    for (int i = 1; i <= T; ++i) {
        cin >> N;
        cin >> P;

        cout << "Case #" << i << ": " << findPath(P, N) << endl;
    }

    return 0;
}

string findPath(string &P, int N) {
    char start_path = P.front();
    char end_path = P.back();

    if (start_path != end_path) {
        return string(N - 1, invertPath(start_path)) + string(N - 1, invertPath(end_path));
    }

    int cnt = 0, pos = 0;
    for (auto iter = P.crbegin(); iter != P.crend(); ++iter) {
        if (*iter == start_path) {
            continue;
        }

        ++cnt;
        ++pos;
        if (*(iter + 1) == *iter) {
            break;
        }
    }

    return string(N - 1 - pos, invertPath(start_path)) + string(N - 1, end_path) + string(pos, invertPath(start_path));
}

char invertPath(char path) {
    return path == 'S' ? 'E' : 'S';
}
