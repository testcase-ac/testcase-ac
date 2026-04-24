#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e3 + 1;
struct edge {
    int v, w;
    bool operator<(const edge &rhs) const {
        return w > rhs.w;
    }
};
vector<edge> adj[MX];
int dist[MX], prv[MX], N, M;
void dijkstra(int ign_a, int ign_b) {
    memset(dist, 0x3f, sizeof(dist));
    memset(prv, -1, sizeof(prv));
    priority_queue<edge> pq;
    pq.push({1, 0});
    dist[1] = 0;
    while(!pq.empty()) {
        auto [u, curw] = pq.top();
        pq.pop();
        if(curw > dist[u]) continue;
        for(auto [v, w]: adj[u]) {
            if((u == ign_a && v == ign_b) || (u == ign_b && v == ign_a))
                continue;
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                prv[v] = u;
                pq.push({v, dist[v]});
            }
        }
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    dijkstra(-1, -1);
    vector<int> path;
    for(int i = N; i != -1; i = prv[i])
        path.push_back(i);
    int ans = 0;
    for(int i = 0; i < path.size() - 1; i++) {
        int u = path[i], v = path[i + 1];
        dijkstra(u, v);
        ans = max(ans, dist[N]);
    }
    cout << ans;
}
