#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 101;
vector<int> adj[MX], child[MX];
struct edge {
    int u, v;
};
vector<edge> backedges;

int seen[MX], n, m;

void dfs(int i, int p) {
    seen[i] = 1;
    for(int a: adj[i]) {
        if(a == p) continue;
        if(seen[a]) {
            if(seen[a] == 1) {
                // printf("backedge is %d %d\n", i, a);
                backedges.push_back({i, a});
            }

        } else {
            child[i].push_back(a);
            dfs(a, i);
        }
    }
    seen[i] = 2;
}
int disabled[MX], dp[MX][2];

int solve(int i, int p) {
    int off_sum = 0, all_sum = 0;
    for(int a: child[i]) {
        solve(a, i);
        off_sum += dp[a][0];
        all_sum += max(dp[a][0], dp[a][1]);
    }
    if(disabled[i]) {
        dp[i][0] = all_sum;
        dp[i][1] = INT_MIN;
    } else {
        dp[i][0] = all_sum;
        dp[i][1] = off_sum + 1;
    }
    return max(dp[i][0], dp[i][1]);
}

int ans = 0;
void determine_disable(int t) {
    if(t == backedges.size()) {
        int s = solve(1, 0);
        // for(int i = 1; i <= n; i++) {
        //     printf("%d ", !!disabled[i]);
        // }
        // printf(" -> s = %d\n", s);
        ans = max(ans, solve(1, 0));
        return;
    }
    auto [u, v] = backedges[t];
    disabled[u]++;
    determine_disable(t + 1);
    disabled[u]--;
    disabled[v]++;
    determine_disable(t + 1);
    disabled[v]--;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    while(m--) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    determine_disable(0);
    cout << ans;
}
