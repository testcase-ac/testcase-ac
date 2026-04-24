#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
using ll = long long;
const ll INF = (ll)4e18;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input graph
    int N = inf.readInt();
    int M = inf.readInt();
    vector<vector<pair<int,int>>> adj(N+1);
    // Store edges in a map for existence and weight lookup
    map<pair<int,int>, int> edgeW;
    for (int i = 0; i < M; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        int c = inf.readInt();
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
        pii e = a < b ? make_pair(a,b) : make_pair(b,a);
        // In case of multiple edges, keep the smallest weight
        if (!edgeW.count(e) || edgeW[e] > c)
            edgeW[e] = c;
    }

    // Compute original shortest distances from node 1
    vector<ll> dist(N+1, INF);
    dist[1] = 0;
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    pq.push({0, 1});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto &pr : adj[u]) {
            int v = pr.first, w = pr.second;
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    // Read contestant's output
    int K = ouf.readInt();
    // Check K
    if (N == 1) {
        if (K != 0)
            ouf.quitf(_wa, "N = 1, expected K = 0, found K = %d", K);
    } else {
        if (K != N-1)
            ouf.quitf(_wa, "expected %d edges for a spanning tree, found %d", N-1, K);
    }

    // Read and validate edges
    set<pii> usedEdges;
    vector<vector<pair<int,int>>> tree(N+1);
    for (int i = 0; i < K; i++) {
        int a = ouf.readInt(1, N, format("edge[%d].first", i+1).c_str());
        int b = ouf.readInt(1, N, format("edge[%d].second", i+1).c_str());
        if (a == b)
            ouf.quitf(_wa, "edge %d is a loop on node %d", i+1, a);
        pii e = a < b ? make_pair(a,b) : make_pair(b,a);
        if (usedEdges.count(e))
            ouf.quitf(_wa, "edge (%d, %d) is repeated", e.first, e.second);
        auto it = edgeW.find(e);
        if (it == edgeW.end())
            ouf.quitf(_wa, "edge (%d, %d) does not exist in the original graph", a, b);
        int w = it->second;
        usedEdges.insert(e);
        tree[a].push_back({b, w});
        tree[b].push_back({a, w});
    }

    // Check connectivity and compute tree distances from 1
    vector<ll> tdist(N+1, INF);
    queue<int> q;
    tdist[1] = 0;
    q.push(1);
    vector<bool> vis(N+1, false);
    vis[1] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &pr : tree[u]) {
            int v = pr.first, w = pr.second;
            if (!vis[v]) {
                vis[v] = true;
                tdist[v] = tdist[u] + w;
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        if (!vis[i])
            ouf.quitf(_wa, "node %d is not reachable from node 1 in the restored network", i);
    }

    // Check distances match the original shortest paths
    for (int i = 1; i <= N; i++) {
        if (tdist[i] != dist[i]) {
            ouf.quitf(_wa,
                "distance to node %d in the restored tree is %lld, "
                "but original shortest distance is %lld",
                i, tdist[i], dist[i]);
        }
    }

    // All checks passed
    quitf(_ok, "Network restored correctly with %d edges", K);
    return 0;
}
