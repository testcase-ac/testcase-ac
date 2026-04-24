#include <bits/stdc++.h>
using namespace std;
int dp[2][101][101][2], A[3001], B[101], N, M;
void update(int &a, int b) {
    if(a < b) a = b;
}
int solve() {
    memset(dp, 0x8f, sizeof(dp));
    dp[0][0][0][0] = 0;
    for(int i = 0; i <= N; i++) {
        int c = i & 1, p = c ^ 1;
        if(i) {
            memset(dp[c], 0x8f, sizeof(dp[0]));
        }
        for(int u = 0; u <= M; u++) {
            for(int nu = 0; nu <= M; nu++) {
                if(nu) {
                    update(dp[c][u][nu][0], dp[c][u][nu - 1][1]);
                }
                if(u) {
                    update(dp[c][u][nu][1], dp[c][u - 1][nu][0]);
                }
                if(i) {
                    update(dp[c][u][nu][0], dp[p][u][nu][1]);
                    update(dp[c][u][nu][1], dp[p][u][nu][0] + A[i]);
                }
                update(dp[c][u][nu][1], dp[c][u][nu][0]);
            }
        }
    }
    int use_sum = 0, ans = 0;
    for(int u = 0; u <= M; u++) {
        use_sum += B[u];
        update(ans, dp[N & 1][u][M - u][1] + use_sum);
    }
    return ans;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    cin >> M;
    for(int i = 1; i <= M; i++) cin >> B[i];
    sort(B + 1, B + M + 1, greater<int>());
    cout << solve();
}
