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
                Edge &e = edges[i];
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
                Edge &e = edges[par[c]];
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
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    while(true) {
        int R, C;
        cin >> R >> C;
        if(!R && !C)
            break;
        vector<pair<int, int>> children, house;
        for(int r = 0; r < R; r++) {
            string s;
            cin >> s;
            for(int c = 0; c < C; c++) {
                if(s[c] == 'm') {
                    children.push_back({r, c});
                } else if(s[c] == 'H') {
                    house.push_back({r, c});
                }
            }
        }
        MCMF mcmf(children.size() + house.size() + 2);
        int src = children.size() + house.size(), sink = children.size() + house.size() + 1;
        for(int i = 0; i < children.size(); i++) {
            mcmf.addedge(src, i, 1, 0);
        }
        for(int i = 0; i < house.size(); i++) {
            mcmf.addedge(children.size() + i, sink, 1, 0);
        }
        for(int c = 0; c < children.size(); c++) {
            for(int h = 0; h < house.size(); h++) {
                int d = abs(children[c].first - house[h].first) + abs(children[c].second - house[h].second);
                mcmf.addedge(c, children.size() + h, 1, d);
            }
        }
        auto [mc, mf] = mcmf.solve(src, sink);
        cout << mc << '\n';
    }
}
