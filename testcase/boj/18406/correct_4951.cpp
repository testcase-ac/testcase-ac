#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define int long long

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    int left = 0, right = 0;
    cin >> s;
    for(int i = 0; i < s.size(); i++) {
        if(i < s.size() / 2 == 0) {
            left += s[i] - '0';
        } else {
            right += s[i] - '0';
        }
    }
    cout << (left == right ? "LUCKY" : "READY") << '\n';
}
