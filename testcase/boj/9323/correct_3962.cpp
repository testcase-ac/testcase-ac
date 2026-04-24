#include <bits/stdc++.h>
using namespace std;

const int MX = 201;
double dp[MX][2];
struct edge {
    int u, prob, dist;
};
struct elem {
    int u, t;
    double dist;
    bool operator<(const elem& rhs) const {
        return dist > rhs.dist;
    }
};
void solve() {
    int n, m, start, end, s, p, y;
    cin >> n >> m >> start >> end >> s >> p >> y;
    vector<vector<edge>> adj;
    adj.resize(n+1);
    while(m--) {
        int u, v, prob, dist;
        cin >> u >> v >> prob >> dist;
        adj[u].push_back({v, prob, dist});
        adj[v].push_back({u, prob, dist});
    }
    for(int i = 0; i < MX; i++) {
        dp[i][0] = dp[i][1] = 1e18;
    }
    priority_queue<elem> pq;
    dp[start][1] = 0;
    pq.push({start, 1, 0});
    while(pq.size()) {
        auto [u, t, dist] = pq.top();
        pq.pop();
        if(dp[u][t] < dist) continue;
        for(auto [v, prob, dist_edge] : adj[u]) {
            // buy ticket
            double val = dp[u][t] + (t ? s : 0) + p * dist_edge;
            if(val < dp[v][0]) {
                dp[v][0] = val;
                pq.push({v, 0, val});
            }

            // not buy ticket
            val = dp[u][t] + prob / 100.0 * (y + p * dist_edge);
            if(val < dp[v][1]) {
                dp[v][1] = val;
                pq.push({v, 1, val});
            }
        }
    }

    double ans = min(dp[end][0], dp[end][1]);
    cout << fixed << setprecision(2) << ans << '\n';
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        solve();
    }
}
