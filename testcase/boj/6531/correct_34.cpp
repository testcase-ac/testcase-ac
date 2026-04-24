#include <bits/stdc++.h>
using namespace std;
vector<vector<char>> dp;
string s;
// check is elementlist
bool rec(int l, int r) {
    int len = r-l+1;
    if(len <= 1) {
        return 1;
    } else if(len == 2) {
        return s[l] == '{' && s[r] == '}';
    }
    char &res = dp[l][r];
    if(res != 42) return res;
    res = s[l+1] == ',' && rec(l+2, r);
    if(!res && s[l] == '{') {
        for(int t=l+1; t<=r; t++) {
            if(s[t] == '}' && rec(l+1, t-1)) {
                res = (t == r) || (s[t+1] == ',' && t+2 <= r && rec(t+2, r));
                if(res) {
                    break;
                }
            }
        }
    }
    return res;
}
bool solve() {
    cin >> s;
    int N = s.size();
    dp = vector<vector<char>>(N, vector<char>(N, 42));
    return s[0] == '{' && s[N-1] == '}' && rec(1, N-2);
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    for(int t=1; t<=T; t++) {
        bool res = solve();
        cout << "Word #" << t << ": " << (res ? "Set\n" : "No Set\n");
    }
}
