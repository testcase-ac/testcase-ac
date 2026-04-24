#include <bits/stdc++.h>
using namespace std;
int solve() {
    string a, b;
    cin >> a >> b;
    int N = a.size(), M = b.size();
    int kind = 0;
    vector<int> totcnt(256);
    for(char c: a) {
        totcnt[c]++;
    }
    for(char c: b) {
        totcnt[c]++;
    }
    for(char c='a'; c<='z'; c++) {
        if(totcnt[c]) kind++;
    }
    a = " " + a;
    b = " " + b;
    vector<vector<int>> dp(a.size(), vector<int>(b.size(), INT_MAX));
    dp[0][0] = 0;
    vector<int> curcnt(256);
    for(int i=0; i<a.size(); i++) {
        curcnt[a[i]]++;
        for(int j=0; j<b.size(); j++) {
            curcnt[b[j]]++;
            int pos = i+j;
            if(i) {
                int v;
                if(totcnt[a[i]] == 1) {
                    v = dp[i-1][j];
                } else if(curcnt[a[i]] == 1) {
                    v = dp[i-1][j] - pos;
                } else if(curcnt[a[i]] == totcnt[a[i]]) {
                    v = dp[i-1][j] + pos;
                } else {
                    v = dp[i-1][j];
                }
                dp[i][j] = min(dp[i][j], v);
            }
            if(j) {
                int v;
                if(totcnt[b[j]] == 1) {
                    v = dp[i][j-1];
                } else if(curcnt[b[j]] == 1) {
                    v = dp[i][j-1] -  pos;
                } else if(curcnt[b[j]] == totcnt[b[j]]) {
                    v = dp[i][j-1] + pos;
                } else {
                    v = dp[i][j-1];
                }
                dp[i][j] = min(dp[i][j], v);
            }
        }
        for(int j=0; j<b.size(); j++) {
            curcnt[b[j]]--;
        }
    }
    return dp[a.size()-1][b.size()-1];
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        cout << solve() << '\n';
    }
}
