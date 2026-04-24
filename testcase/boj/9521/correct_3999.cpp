#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e6 + 1, MOD = 1e9 + 7;
int N, K, arr[MX], dp[MX];
int lvl[MX];
vector<int> adj[MX];
int ans = 1, allsz, cycsz;
void dfs(int i, int p) {
    allsz++;
    for(int a: adj[i]) {
        if(a == p) continue;
        if(!lvl[a]) {
            lvl[a] = lvl[i] + 1;
            dfs(a, i);
        } else {
            if(lvl[a] < lvl[i]) {
                cycsz = lvl[i] - lvl[a] + 1;
            }
        }
    }
}
void multiple(int t) {
    ans = (ans * t) % MOD;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> K;
    int mult = 1;
    for(int i = 1; i <= N; i++) {
        dp[i] = (K * mult - (i > 2 ? dp[i - 1] : 0)) % MOD;
        // printf("%lld\n", dp[i]);
        mult = (mult * (K - 1)) % MOD;
    }
    for(int i = 1; i <= N; i++) {
        cin >> arr[i];
        if(arr[arr[i]] != i) {
            adj[arr[i]].push_back(i);
            adj[i].push_back(arr[i]);
        }
    }
    for(int i = 1; i <= N; i++) {
        if(!lvl[i]) {
            lvl[i] = 1;
            allsz = 0;
            cycsz = 1;
            dfs(i, 0);
            // printf("allsz = %d, cycsz = %d\n", allsz, cycsz);
            multiple(dp[cycsz]);
            for(int i = 0; i < (allsz - cycsz); i++) {
                multiple(K - 1);
            }
        }
    }
    cout << ans << '\n';
}
