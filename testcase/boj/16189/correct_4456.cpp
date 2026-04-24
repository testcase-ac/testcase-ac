#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    int t;
    cin >> s >> t;
    bool ok = 1;
    for(int i=0; i<s.size(); i++) {
        if(s[i] != s[s.size() - 1 - i]) {
            ok = 0;
            break;
        }
    }
    cout << (ok ? "YES" : "NO");
}
