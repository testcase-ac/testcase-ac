#include <bits/stdc++.h>
using namespace std;
#define int long long
struct Edge {
    int u, v, w, cap, flow;
};
const int INF = 0x3f3f3f3f;
struct MCMF {
    int n;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> par, dist, inque;
    MCMF(int _n) {
        n = _n;
        adj.resize(n + 1);
        par.resize(n + 1);
        dist.resize(n + 1);
        inque.resize(n + 1);
    }
    void addedge(int u, int v, int cap, int w) {
        adj[u].push_back(edges.size());
        edges.push_back({u, v, w, cap, 0});
        adj[v].push_back(edges.size());
        edges.push_back({v, u, -w, cap, cap});
    }
    void spfa(int src) {
        fill(par.begin(), par.end(), -1);
        fill(dist.begin(), dist.end(), INF);
        fill(inque.begin(), inque.end(), 0);
        dist[src] = 0;
        queue<int> que({src});
        while(que.size()) {
            int q = que.front();
            que.pop();
            inque[q] = 0;
            for(int i: adj[q]) {
                Edge& e = edges[i];
                if(e.flow < e.cap && dist[e.v] > dist[e.u] + e.w) {
                    dist[e.v] = dist[e.u] + e.w;
                    par[e.v] = i;
                    if(!inque[e.v]) {
                        inque[e.v] = 1;
                        que.push(e.v);
                    }
                }
            }
        }
    }
    pair<int, int> solve(int src, int sink) {
        int mc = 0, mf = 0;
        while(1) {
            spfa(src);
            if(par[sink] == -1)
                return {mc, mf};
            int flow = INF, c = sink;
            while(c != src) {
                Edge& e = edges[par[c]];
                flow = min(flow, e.cap - e.flow);
                c = e.u;
            }
            c = sink;
            while(c != src) {
                Edge &e = edges[par[c]], &ie = edges[par[c] ^ 1];
                e.flow += flow;
                ie.flow -= flow;
                c = e.u;
            }
            mf += flow;
            mc += dist[sink] * flow;
        }
    }
};

int in_node(int i) {
    return i * 2 - 1;
}

int out_node(int i) {
    return i * 2;
}

int solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges;
    while(m--) {
        int x, y;
        cin >> x >> y;
        edges.push_back({x, y});
    }
    MCMF mcmf(2 * n + 5);  // 2n + 1: src, 2n + 2: sink
    for(int i = 1; i <= n; i++) {
        mcmf.addedge(in_node(i), out_node(i), 1, -1);
    }
    for(int i = 1; i <= n; i++) {
        mcmf.addedge(2 * n + 1, in_node(i + 1), 1, 0);
        mcmf.addedge(out_node(i), 2 * n + 2, 1, 0);
    }

    for(auto [a, b]: edges) {
        mcmf.addedge(out_node(b), in_node(a), 1, 0);
    }
    mcmf.addedge(2 * n + 3, 2 * n + 1, 2, 0);
    mcmf.addedge(2 * n + 2, 2 * n + 4, 2, 0);
    auto [mc, mf] = mcmf.solve(2 * n + 3, 2 * n + 4);
    return -mc;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--)
        cout << solve() << '\n';
}
