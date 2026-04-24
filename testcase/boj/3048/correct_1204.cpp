#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n1, n2;
    cin >> n1 >> n2;
    int n = n1 + n2;

    string first, second;
    cin >> first >> second;
    reverse(first.begin(), first.end());

    string s = first + second;

    vector<bool> isRight(n, false);
    for (int i = 0; i < n1; i++) {
        isRight[i] = true;
    }

    int t;
    cin >> t;

    while (t--) {
        int i = 0;
        while (i < n - 1) {
            if (isRight[i] && !isRight[i + 1]) {
                swap(s[i], s[i + 1]);
                swap(isRight[i], isRight[i + 1]);
                i += 2;
            } else {
                i++;
            }
        }
    }

    cout << s;
    return 0;
}
