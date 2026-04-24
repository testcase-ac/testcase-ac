#include <bits/stdc++.h>
using namespace std;
#define int long long
int arr[17][17], dp[1<<16], N;
int rec(int bm) {
    if(bm == 0)
        return 0;
    int &res = dp[bm];
    if(res != -1) {
        return res;
    }
    res = INT_MAX;
    for(int i=1; i<=N; i++) {
        if(!(bm & (1<<(i-1)))) continue;
        int added = arr[i][0];
        for(int j=1; j<=N; j++) {
            if(i == j) continue;
            if(!(bm & (1<<(j-1)))) continue;
            added = min(added, arr[i][j]);
        }
        res = min(res, rec(bm^(1<<(i-1))) + added);
    }
    return res;
}
int solve() {
    cin >> N;
    if(N == 0) {
        exit(0);
    }
    for(int i=1; i<=N; i++) {
        for(int j=0; j<=N; j++) {
            cin >> arr[i][j];
        }
    }
    memset(dp, -1, sizeof dp);

    return rec((1<<N)-1);
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    while(true) {
        cout << solve() << '\n';
    }

}
