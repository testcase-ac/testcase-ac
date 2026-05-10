#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)4e18;

vector<ll> dijkstra(int n, int src, const vector<vector<pair<int,int>>> &adj) {
    vector<ll> dist(n+1, INF);
    dist[src] = 0;
    // min-heap of (dist, node)
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto &ed : adj[u]) {
            int v = ed.first;
            int w = ed.second;
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // Read n, m, t
        int n = inf.readInt(2, 2000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 50000, "m");
        inf.readSpace();
        int t = inf.readInt(1, 100, "t");
        inf.readEoln();
        // Read s, g, h
        int s = inf.readInt(1, n, "s");
        inf.readSpace();
        int g = inf.readInt(1, n, "g");
        inf.readSpace();
        int h = inf.readInt(1, n, "h");
        inf.readEoln();
        ensuref(g != h, "g and h must be different (got g=%d, h=%d)", g, h);
        // Read edges
        vector<vector<pair<int,int>>> adj(n+1);
        set<pair<int,int>> seenEdge;
        int ghLen = -1;
        for (int i = 0; i < m; i++) {
            int a = inf.readInt(1, n, "a");
            inf.readSpace();
            int b = inf.readInt(1, n, "b");
            inf.readSpace();
            int d = inf.readInt(1, 1000, "d");
            inf.readEoln();
            // a < b
            ensuref(a < b, "Edge %d: require a < b (got a=%d, b=%d)", i, a, b);
            // no multiple edges
            pair<int,int> e = {a, b};
            ensuref(!seenEdge.count(e),
                    "Multiple edges between %d and %d at edge index %d", a, b, i);
            seenEdge.insert(e);
            // build adjacency
            adj[a].push_back({b, d});
            adj[b].push_back({a, d});
            // record g-h edge length
            if ((a == g && b == h) || (a == h && b == g)) {
                ghLen = d;
            }
        }
        ensuref(ghLen != -1, "No edge between g=%d and h=%d found", g, h);
        // Read candidate destinations
        vector<int> cand(t);
        set<int> seenCand;
        for (int i = 0; i < t; i++) {
            int x = inf.readInt(1, n, "x");
            inf.readEoln();
            ensuref(x != s, "Candidate %d equals start s (%d)", i, s);
            ensuref(!seenCand.count(x),
                    "Duplicate candidate destination %d at index %d", x, i);
            seenCand.insert(x);
            cand[i] = x;
        }
        // Check that the g-h edge is on some shortest path from s to a candidate
        // Compute dists
        vector<ll> ds = dijkstra(n, s, adj);
        vector<ll> dg = dijkstra(n, g, adj);
        vector<ll> dh = dijkstra(n, h, adj);
        bool usesGH = false;
        for (int x : cand) {
            ll best = ds[x];
            // path s->g->h->x or s->h->g->x
            ll via1 = ds[g] + ghLen + dh[x];
            ll via2 = ds[h] + ghLen + dg[x];
            if (best == via1 || best == via2) {
                usesGH = true;
                break;
            }
        }
        ensuref(usesGH,
                "The edge g-h is not used in any shortest path to given candidates");
    }
    inf.readEof();
    return 0;
}
