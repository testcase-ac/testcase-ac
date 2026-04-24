#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 2e5+5;
vector<int> adj[MX], adjinv[MX];
int weak[MX], strong[MX], dp[MX], out[MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    deque<int> out_zeros;
    for(int i=1; i<=N; i++) {
        cin >> weak[i] >> strong[i];
        int t;
        cin >> t;
        while(t--) {
            int x;
            cin >> x;
            adj[i].push_back(x);
            adjinv[x].push_back(i);
            out[i]++;
        }
        if(!out[i]) {
            out_zeros.push_back(i);
        }
    }
    vector<int> by_strong(N);
    iota(by_strong.begin(), by_strong.end(), 1);
    sort(by_strong.begin(), by_strong.end(), [&](int i, int j) {
        return strong[i] < strong[j];
    });
    int ptr = 0;
    while(ptr < N) {
        while(out_zeros.size()) {
            int t = out_zeros.front();
            out_zeros.pop_front();
            if(dp[t]) continue;
            int w = weak[t];
            for(int a: adj[t]) {
                w += dp[a];
            }
            for(int a: adjinv[t]) {
                out[a]--;
                if(!out[a]) {
                    out_zeros.push_back(a);
                }
            }
            dp[t] = min(w, strong[t]);
            // printf("at out_zero, dp %lld = %lld. weak = %lld, strong = %lld\n", t, dp[t], w, strong[t]);
        }
        out_zeros.clear();
        while(ptr < N && dp[by_strong[ptr]]) {
            // printf("skipped %lld\n", by_strong[ptr]);
            ptr++;
        }
        if(ptr == N) {
            break;
        }

        int cur = by_strong[ptr];
        for(int a: adjinv[cur]) {
            out[a]--;
            if(!out[a]) {
                out_zeros.push_back(a);
            }
        }
        dp[cur] = strong[cur];
        // printf("at last, dp %lld = %lld\n", cur, strong[cur]);
    }
    cout << dp[1];
}
