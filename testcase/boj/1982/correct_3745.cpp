#include <bits/stdc++.h>
using namespace std;
#define int long long
struct room {
    int ppl, cost;
    void read() {
        cin >> ppl >> cost;
    }
};
int dp[2][101][101][101];
room rooms[101];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int M, F, R, C;
    cin >> M >> F >> R >> C;
    for(int i = 0; i < R; i++) {
        rooms[i].read();
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0][0] = 0;

    auto set_dp = [&](int r, int m, int f, int c, int val) {
        dp[r & 1][m][f][c] = min(dp[r & 1][m][f][c], val);
    };
    for(int r = 0; r < R; r++) {
        auto [ppl, cost] = rooms[r];
        memset(dp[(r + 1) & 1], 0x3f, sizeof(dp[(r + 1) & 1]));
        for(int m = 0; m <= M; m++) {
            for(int f = 0; f <= F; f++) {
                for(int c = 0; c <= C; c++) {
                    int male_mx = min(M - m, ppl);
                    set_dp(r + 1, m + male_mx, f, c, dp[r & 1][m][f][c] + cost);

                    int female_mx = min(F - f, ppl);
                    set_dp(r + 1, m, f + female_mx, c, dp[r & 1][m][f][c] + cost);

                    if(c < C && m < M && f < F && ppl >= 2)
                        set_dp(r + 1, m + 1, f + 1, c + 1, dp[r & 1][m][f][c] + cost);
                    set_dp(r + 1, m, f, c, dp[r & 1][m][f][c]);
                }
            }
        }
    }
    int ans = INT_MAX;
    for(int c = 0; c <= C; c++) {
        ans = min(ans, dp[R & 1][M][F][c]);
    }
    if(ans >= INT_MAX)
        cout << "Impossible" << endl;
    else
        cout << ans << endl;
}
