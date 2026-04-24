#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5+5;
struct edge {
    int v, w;
};
vector<edge> adj[MX];
tuple<int, int, int, int> dfs(int i, int p) {
    if(adj[i].size() == 1) {
        int w = adj[i][0].w;
        return {w, w*w, 1, 0};
    } else {
        int la = 0, lsq = 0, lcnt = 0, ra = 0, rsq = 0, rcnt = 0, pw = -1, anssum = 0;
        for(auto t: adj[i]) {
            if(t.v == p) {
                pw = t.w;
                continue;
            }
            auto [a, asq, acnt, tans] = dfs(t.v, i);
            if(!la) {
                la = a;
                lsq = asq;
                lcnt = acnt;
            } else {
                ra = a;
                rsq = asq;
                rcnt = acnt;
            }
            anssum += tans;
        }
        int ans = lsq * rcnt + rsq * lcnt + 2 * la * ra;
        int asum = la+ra, sqsum = lsq+rsq, cnt = lcnt+rcnt;
        if(pw != -1) {
            sqsum += pw * pw * cnt + 2 * pw * asum;
            asum += pw * cnt;
        }
        return {asum, sqsum, cnt, ans + anssum};
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    for (int i=0;i<N-1;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if(i == 0) {
            adj[u].push_back({N+1, w});
            adj[N+1].push_back({u, w});
            adj[v].push_back({N+1, 0});
            adj[N+1].push_back({v, 0});
        } else {
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
    }

    auto [sum, sqsum, cnt, ans] = dfs(N+1, 0);

    cout << ans;
}
