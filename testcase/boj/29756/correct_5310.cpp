#include <bits/stdc++.h>
using namespace std;
#define int long long

int dp[1001][101];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, K;
    cin >> N >> K;
    vector<int> S(N), H(N);
    for(auto &t: S) cin >> t;
    for(auto &t: H) cin >> t;
    fill(dp[0], dp[0]+101, INT_MIN);
    dp[0][100] = 0;
    for(int i=0; i<N; i++) {
        for(int h=0; h<=100; h++) {
            if(h >= H[i]) {
                int &upd = dp[i+1][min(100ll, h-H[i]+K)];
                upd = max(upd, dp[i][h] + S[i]);
            }
            int &upd = dp[i+1][min(100ll, h+K)];
            upd = max(upd, dp[i][h]);
        }
    }
    cout << *max_element(dp[N], dp[N]+101);
}
