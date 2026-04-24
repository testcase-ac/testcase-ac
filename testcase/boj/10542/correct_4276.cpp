#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 5e5 + 1;
vector<int> adj[MX];
pair<int, int> back[MX];
vector<int> child[MX];
int seen[MX], dp[MX][2][2], gp;
void pre(int i, int p) {
    seen[i] = 1;
    for(int a: adj[i]) {
        if(a == p) continue;
        if(seen[a]) {
            back[gp] = {i, a};
            continue;
        } else {
            child[i].push_back(a);
            pre(a, i);
        }
    }
}

void dfs(int i, int p, int bm) {
    seen[i] = 1;
    if(i == (bm ? back[gp].second : back[gp].first)) {
        dp[i][bm][0] = 0;
        dp[i][bm][1] = INT_MIN;
    } else {
        dp[i][bm][0] = 0;
        dp[i][bm][1] = 1;
    }
    int all_sum = 0, no_sum = 0;
    for(int c: child[i]) {
        dfs(c, i, bm);
        dp[i][bm][0] += max(dp[c][bm][0], dp[c][bm][1]);
        dp[i][bm][1] += dp[c][bm][0];
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        adj[t].push_back(i);
        adj[i].push_back(t);
    }
    for(int i = 1; i <= n; i++) {
        if(seen[i]) continue;
        gp = i;
        pre(i, 0);
    }
    memset(seen, 0, sizeof seen);
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(seen[i]) continue;
        gp = i;
        dfs(i, 0, 0);
        dfs(i, 0, 1);
        ans += max({dp[i][0][0], dp[i][0][1], dp[i][1][0], dp[i][1][1]});
    }
    cout << ans;
}
