#include <bits/stdc++.h>
using namespace std;
#define int long long
struct cow {
    int h, w, p;
};
cow cows[20];
int dp[1 << 20];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, H;
    cin >> N >> H;
    for(int i = 0; i < N; i++) {
        cin >> cows[i].h >> cows[i].w >> cows[i].p;
    }
    memset(dp, -1, sizeof dp);
    dp[0] = LLONG_MAX;
    int ans = -1;
    for(int bm = 1; bm < (1 << N); bm++) {
        int h = 0;
        for(int i = 0; i < N; i++) {
            if(!(bm & (1 << i))) continue;
            h += cows[i].h;
            int prev = bm ^ (1 << i);
            if(dp[prev] >= cows[i].w) {
                dp[bm] = max(dp[bm], min(dp[prev] - cows[i].w, cows[i].p));
            }
        }
        if(h >= H) {
            ans = max(ans, dp[bm]);
        }
    }
    if(ans == -1) {
        cout << "Mark is too tall" << '\n';
    } else {
        cout << ans << endl;
    }
}
