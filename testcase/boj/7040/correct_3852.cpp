#include <bits/stdc++.h>
using namespace std;
struct edge {
    int u, v, w;
};
const int MX = 1001;
vector<edge> edges;
int dist[MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, ML, MD;
    cin >> N >> ML >> MD;
    for(int i = 0; i < ML; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
    for(int i = 0; i < MD; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        edges.push_back({v, u, -w});
    }
    for(int i = 2; i <= N; i++) {
        edges.push_back({i, i - 1, 0});
    }
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    bool relaxed = 0;
    for(int i = 0; i < N; i++) {
        relaxed = 0;
        for(auto [u, v, w]: edges) {
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                relaxed = 1;
            }
        }
    }
    if(relaxed) {
        cout << -1;
    } else if(dist[N] >= 0x3f3f3f3f) {
        cout << -2;
    } else {
        cout << dist[N];
    }
}
