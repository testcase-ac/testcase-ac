#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
int dp[101][5555][101];
int f(int a, int b, int c) {
    if(c < 0) return f(a, b, 0);
    if(c > a || b < 0) return 0;
    if(a == 0 && b == 0) return 1;
    if(a == 0 && b > 0) return 0;
    int &ret = dp[a][b][c];
    if(ret != -1) return ret;
    ret = f(a-1, b-c, c-1) + f(a, b, c+1);
    ret %= MOD;
    return ret;
}
int32_t main() {
    memset(dp, -1, sizeof(dp));
    int h, s;
    cin >> h >> s;
    cout << f(h, s, 0);
}
