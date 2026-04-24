#include <bits/stdc++.h>
using namespace std;
#define int long long
struct edge {
    int u, w;
    bool operator<(const edge &e) const {
        return w > e.w;
    }
};
const int MX = 3001;
vector<edge> adj[MX];
int N, M, K, dist[MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> M >> K;
    for(int i = 0; i < M; i++) {
        int a, b, l;
        cin >> a >> b >> l;
        adj[a].push_back({b, l});
        adj[b].push_back({a, l});
    }
    memset(dist, 0x3f, sizeof dist);
    priority_queue<edge> pq;
    while(K--) {
        int t;
        cin >> t;
        pq.push({t, 0});
        dist[t] = 0;
    }
    while(!pq.empty()) {
        auto [u, w] = pq.top();
        pq.pop();
        if(dist[u] < w)
            continue;
        for(edge e: adj[u]) {
            if(dist[e.u] > w + e.w) {
                dist[e.u] = w + e.w;
                pq.push({e.u, dist[e.u]});
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= N; i++) {
        for(auto [u, w]: adj[i]) {
            ans = max(ans, (dist[u] + dist[i] + w + 1) / 2);
        }
    }
    cout << ans;
}
