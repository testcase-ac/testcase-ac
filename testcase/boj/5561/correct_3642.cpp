#include <bits/stdc++.h>
using namespace std;

const int MX = 10001;
int dp[2][MX], arr[MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
    dp[1][1] = 0;
    auto relax = [](int &t, int v) {
        t = min(t, v);
    };
    for(int i = 1; i < N; i++) {
        memset(dp[(i + 1) & 1], 0x3f, sizeof dp[(i + 1) & 1]);
        for(int j = 1; j <= i; j++) {
            relax(dp[(i + 1) & 1][j + 1], dp[i & 1][j]);
            relax(dp[(i + 1) & 1][i - j + 1], dp[i & 1][j] + arr[i]);
        }
    }
    cout << dp[N & 1][N / 2];
}
