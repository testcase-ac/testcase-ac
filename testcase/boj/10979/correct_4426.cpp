#include <bits/stdc++.h>
using namespace std;
#define int long long
struct edge {
    int t, g, u;
};
struct info {
    int t, g, i, u;
    bool operator<(const info &x) const {
        return t > x.t || (t == x.t && g < x.g);
    }
};
pair<int, int> solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<edge>> adj(N+1);
    vector<vector<info>> dist(2, vector<info>(N+1));
    for(int i=2; i<=N; i++) {
        dist[0][i].t = dist[0][i].g = dist[1][i].t = dist[1][i].g = LLONG_MAX/2;
    }
    dist[1][1].t = dist[1][1].g = LLONG_MAX/2;
    for(int i=0; i<M; i++) {
        int x, y, t, g;
        cin >> x >> y >> t >> g;
        adj[x].push_back({t, g, y});
        adj[y].push_back({t, g, x});
    }
    priority_queue<info> pq;
    pq.push({0, 0, 0, 1});
    while(pq.size()) {
        auto tp = pq.top();
        int t = tp.t, g = tp.g, i = tp.i, u = tp.u;
        pq.pop();
        if(tp < dist[i][u]) continue;
        for(auto &e: adj[u]) {
            info n = {t + e.t, g + e.g, i, e.u};
            if(dist[i][e.u] < n) {
                if(!i) {
                    dist[1][e.u] = dist[0][e.u];
                }
                dist[i][e.u] = n;
                pq.push(n);
            } else if(!i && dist[1][e.u] < n) {
                n.i = 1;
                dist[n.i][e.u] = n;
                pq.push(n);
            }
        }
    }
    if(dist[0][N].t == dist[1][N].t) {
        return {dist[0][N].t, dist[0][N].g};
    } else {
        return {dist[1][N].t, dist[1][N].g};
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    for(int i=1; i<=T; i++) {
        auto [a, b] = solve();
        printf("Game #%lld: Suckzoo ends game in time %lld, earning %lld garnet(s).\n", i, a, b);
    }
}
