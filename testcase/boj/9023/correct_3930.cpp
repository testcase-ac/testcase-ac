#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, N) for(int i=0; i<N; i++)
vector<int> A, B;
int C, D, d;
const int MX = 102;
int dp[MX][MX][2][2];
int f(int i, int j, int ri, int rj) {
    if(ri && rj)
        return INT_MAX;
    if(i == -1 && j == -1) {
        return 0;
    } else if(i == -1) {
        return (C+d) * (j+1) + D;
    } else if(j == -1) {
        return (C+d) * (i+1) + D;
    }
    int &res = dp[i][j][ri][rj];
    if(res != -1) return res;
    res = INT_MAX;
    if(ri == 0 && rj == 1) {
        rep(x, 2) rep(y, 2) {
            res = min(res, f(i-1, j, x, y) + C + (y ? d : D+d));
        }
    } else if(ri == 1 && rj == 0) {
        rep(x, 2) rep(y, 2) {
            res = min(res, f(i, j-1, x, y) + C + (x ? d : D+d));
        }
    } else if(ri == 0 && rj == 0) {
        rep(x, 2) rep(y, 2) {
            res = min(res, f(i-1, j-1, x, y) + (A[i] == B[j] ? C : 2*C ));
        }
    }
    return res;
}
int solve() {
    cin >> C >> D >> d;
    int t;
    A.clear();
    B.clear();
    memset(dp, -1, sizeof dp);
    while(cin >> t) {
        if(!t) break;
        A.push_back(t);
    }
    while(cin >> t) {
        if(!t) break;
        B.push_back(t);
    }
    int ans = INT_MAX;
    rep(x, 2) rep(y, 2) {
        ans = min(ans, f(A.size()-1, B.size()-1, x, y));
    }
    return ans;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--)
        cout << solve() << '\n';
}
