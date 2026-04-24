#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 30005;

struct edge {
    int u, v, w;
    bool operator<(const edge &e) const {
        return w > e.w;
    }
};
struct info {
    int v, w;
    bool operator<(const info a) const {
        return w > a.w;
    }
};
vector<pair<int, int>> adj[MX*10], adj_orig[MX];
vector<int> adjinv[MX];
map<pair<int, int>, int> mp;
int deg_acc[MX];
int M, N, K, V, W;
pair<int, int> to_sted(int i) {
    return pair<int, int>{(i == 0 ? 0ll : deg_acc[i-1]), deg_acc[i]};
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> M >> N >> K >> V >> W;
    if(V == W) {
        return !(cout << 0);
    }
    vector<edge> E(M), forbids(K);
    for(int i=0; i<M; i++) {
        cin >> E[i].u >> E[i].v >> E[i].w;
        adjinv[E[i].v].push_back(E[i].u);
        adj_orig[E[i].u].push_back({E[i].v, E[i].w});
    }
    for(int i=0; i<K; i++) {
        cin >> forbids[i].u >> forbids[i].v >> forbids[i].w;
    }
    sort(forbids.begin(), forbids.end(), [](auto a, auto b){
        return tie(a.u, a.v, a.w) < tie(b.u, b.v, b.w);
    });
    deg_acc[0] = adjinv[0].size();
    for(int t=0; t<deg_acc[0]; t++) {
        pair<int, int> k = make_pair(0ll, adjinv[0][t]);
        mp[k] = t;
    }
    // printf("\n0 is mapped to %d - %d\n", 0, deg_acc[0]);
    for(int i=1; i<N; i++) {
        deg_acc[i] = deg_acc[i-1] + adjinv[i].size();
        for(int t=0; t<adjinv[i].size(); t++) {
            pair<int, int> k = make_pair(i, adjinv[i][t]);
            mp[k] = deg_acc[i-1] + t;
        }
        // printf("%d is mapped to %d - %d\n", i, deg_acc[i-1], deg_acc[i]);
    }
    for(auto [u, v, w]: E) {
        auto [st, ed] = to_sted(u);
        // printf("original edge: %d %d, mapped to %d %d\n", u, v, st, ed);
        int nxt = mp[{v, u}];
        for(int a=st; a<ed; a++) {
            // printf("  considering mapped %d\n", a);
            int prv = adjinv[u][a-st];
            // add edge prv -> a -> nxt: a_prv -> nxt_a;
            bool banned = binary_search(forbids.begin(), forbids.end(), edge{prv, u, v}, [](auto a, auto b){
                return tie(a.u, a.v, a.w) < tie(b.u, b.v, b.w);
            });
            if(banned) {
                // printf("    prv = %d, u = %d, v = %d: banned\n", prv, u, v);
                continue;
            }
            // printf("    %d %d %d is unbanned, pushed edge %d - %d\n", prv, u, v, a, nxt);
            adj[a].push_back({nxt, w});
        }
    }
    // do dijkstra
    vector<int> dist(N * 11);
    fill(dist.begin(), dist.end(), LLONG_MAX / 2);
    auto [st_v, ed_v] = to_sted(V);
    priority_queue<info> pq;
    for(int i=st_v; i<ed_v; i++) {
        dist[i] = 0;
        pq.push({i, 0});
    }
    for(auto [v, w]: adj_orig[V]) {
        int nxt = mp[{v, V}];
        dist[nxt] = w;
        pq.push({nxt, w});
    }
    while(pq.size()) {
        auto [v, w] = pq.top();
        pq.pop();
        if(dist[v] < w) continue;
        // printf("dist %d = %d\n", v, w);
        for(auto [u, ew]: adj[v]) {
            if(w + ew < dist[u]) {
                dist[u] = w + ew;
                pq.push({u, dist[u]});
            }
        }
    }
    auto [st_w, ed_w] = to_sted(W);
    auto it = min_element(dist.begin() + st_w, dist.begin() + ed_w);
    if(it == dist.end() || *it >= LLONG_MAX / 2) {
        cout << "-1";
    } else {
        cout << *it;
    }
}
