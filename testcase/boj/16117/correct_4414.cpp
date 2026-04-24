#include <bits/stdc++.h>
#define rep(i,n) for(int i=0; i<(n); i++)
#define sz(x) ((int)(x).size())
#define ll long long
using namespace std;
const int MX = 1007;
int dp[MX][MX], dp2[MX][MX], val[MX][MX];
int n, m;
int rec(int r, int c) {
    if(!(c < m && r >= 0 && r <= n)) return 0;
    if(c >= 0 && dp[r][c] != -1) return dp[r][c];
    int ret = 0;
    ret = rec(r,c+2) + val[r][c+1] + val[r][c+2];
    if(r+1 <= n) ret = max(ret, rec(r+1, c+1) + val[r+1][c+1]);
    if(r-1>=0) ret = max(ret, rec(r-1, c+1) + val[r-1][c+1]);
    dp[r][c] = ret;
    return ret;
}

int rec2(int r, int c) {
    if(!(c < m && r >= 0 && r <= n)) return 0;
    if(c >= 0 && dp2[r][c] != -1) return dp2[r][c];
    int ret = 0;
    ret = rec2(r,c+2);
    if(r+1 <= n) ret = max(ret, rec2(r+1, c+1) + val[r+1][c+1]);
    if(r-1>=0) ret = max(ret, rec2(r-1, c+1) + val[r][c+1]);
    dp2[r][c] = ret;
    return ret;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    memset(dp, -1, sizeof dp);
    memset(dp2, -1, sizeof dp2);
    cin >> n >> m;
    for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) cin >> val[i][j];
    int ans = 0;
    for(int i=1; i<=n; i++) {
        int a = rec(i, 0);
        ans = max(ans, a);
    }
    for(int i=0; i<=n; i++) {
        int a = rec2(i, 0);
        ans = max(ans, a);
    }
    cout << ans;
}
