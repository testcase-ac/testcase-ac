#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 201;
int dp[MX][MX][MX];
int f(int a, int b, int c) {
    if(a == b && b == c) return 1;
    if(a > b) swap(a, b);
    if(b > c) swap(b, c);
    if(a > b) swap(a, b);
    int &res = dp[a][b][c];
    if(res != -1) return res;
    res = INT_MAX;
    if(a > 1) {
        for(int t=1; t<=a/2; t++) {
            res = min(res, f(a-t, b, c) + f(t, b, c));
        }
    }

    if(b > 1) {
        for(int t=1; t<=b/2; t++) {
            res = min(res, f(a, t, c) + f(a, b-t, c));
        }
    }

    if(c > 1) {
        for(int t=1; t<=c/2; t++) {
            res = min(res, f(a, b, c-t) + f(a, b, t));
        }
    }

    return res;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    memset(dp, -1, sizeof dp);
    while(T--) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << f(a, b, c) << '\n';
    }
}
