#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7, MX = 1<<20;
int dp2[MX], dp[MX], p2[MX];
int32_t main() {
    p2[0] = 1;
    for(int i=1; i<MX; i++) {
        p2[i] = (p2[i-1] * 2) % MOD;
    }
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    for(int i=0; i<N; i++) {
        int K, bm = 0;
        cin >> K;
        while(K--) {
            int t;
            cin >> t;
            bm ^= (1<<(t-1));
        }
        dp2[bm]++;
    }
    // SOS dp
    for(int i = 0; i < M; ++i) for(int mask = 0; mask < (1<<M); ++mask){
        if(mask & (1<<i))
            dp2[mask] += dp2[mask^(1<<i)];
    }

    for(int i=0; i<(1<<M); i++) {
        dp[i] = p2[dp2[((1<<M)-1) ^ i]];
    }
    int ans = 0;
    for(int i=1; i<(1<<M); i++) {
        int pc = __builtin_popcountll(i);
        ans += ((pc % 2) ? 1 : -1) * dp[i];
        ans %= MOD;
    }
    cout << (p2[N] - ans + MOD) % MOD;

}
