#include <bits/stdc++.h>
using namespace std;
#define int long long
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    string s, t;
    cin >> s >> t;
    while(t.size() > s.size()) {
        if(t.back() == 'A') {
            t.pop_back();
        } else {
            t.pop_back();
            reverse(t.begin(), t.end());
        }
    }
    cout << (s == t ? 1 : 0) << '\n';
}
