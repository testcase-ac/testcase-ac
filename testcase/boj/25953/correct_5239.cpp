#include <bits/stdc++.h>
using namespace std;
#define int long long
int dist[2][10001];
struct edge {
    int u, v, w;
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, T, M;
    cin >> N >> T >> M;
    int S, E;
    cin >> S >> E;
    memset(dist, 0x3f, sizeof(dist));
    dist[0][S] = 0;
    int inf = dist[0][E];
    for(int t=0; t<T; t++) {
        int cur = t&1, nxt = cur^1;
        vector<edge> ed;
        for(int i=0; i<M; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            ed.push_back({u, v, w});
        }
        memcpy(dist[nxt], dist[cur], sizeof(dist[0]));
        for(auto &[u, v, w]: ed) {
            dist[nxt][v] = min(dist[nxt][v], dist[cur][u] + w);
            dist[nxt][u] = min(dist[nxt][u], dist[cur][v] + w);
        }
    }
    int cur = T & 1;
    if(dist[cur][E] != inf) {
        cout << dist[cur][E];
    } else {
        cout << -1;
    }
}
