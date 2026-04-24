#include <bits/stdc++.h>
using namespace std;
#define int long long
struct chapter {
    int time, pages;
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    vector<chapter> a(M+1);
    for(int i = 1; i <= M; i++) {
        cin >> a[i].time >> a[i].pages;
    }
    vector<vector<int>> dp(M+1, vector<int>(N+1, 0));
    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N; j++) {
            if(j >= a[i].time) {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-a[i].time] + a[i].pages);
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    cout << dp[M][N];
}
