#include <bits/stdc++.h>
using namespace std;
int dp[1<<17][17];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> a(N);
    for(int i = 0; i < N; i++) {
        int t, bm = 0;
        cin >> t;
        while(t--) {
            int x;
            cin >> x;
            x--;
            bm |= 1 << x;
        }
        dp[bm][16]++;
        a[i] = bm;
    }
    vector<int> cur;
    for(int bm=1; bm<(1<<17); bm++) {
        for(int t=16; t>=0; t--) {
            cur.clear();
            for(int i=0; i<17; i++) {
                if(bm & (1<<i)) {
                    cur.push_back(i);
                }
            }
            if(t != 16) {
                dp[bm][t] += dp[bm][t+1];
            }
            if(t >= cur.size()) {
                continue;
            }
            int loc = cur[t];
            if(loc > 0 && !(bm & (1<<(loc-1)))) {
                dp[bm][t] += dp[bm^(1<<loc)^(1<<(loc-1))][t];
            }
        }
    }
    for(int i=0; i<N; i++) {
        cout << dp[a[i]][0] << ' ';
    }
}
