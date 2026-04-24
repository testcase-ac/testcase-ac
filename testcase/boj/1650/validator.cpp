#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int rev;
    int cap;
};

struct Dinic {
    int N;
    vector<vector<Edge>> G;
    vector<int> level, ptr;
    Dinic(int n): N(n), G(n+1), level(n+1), ptr(n+1) {}
    void addEdge(int u, int v, int c) {
        G[u].push_back({v, (int)G[v].size(), c});
        G[v].push_back({u, (int)G[u].size()-1, 0});
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : G[u]) {
                if (level[e.to] < 0 && e.cap > 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }
    int dfs(int u, int t, int pushed) {
        if (u == t || pushed == 0) return pushed;
        for (int &cid = ptr[u]; cid < (int)G[u].size(); cid++) {
            Edge &e = G[u][cid];
            if (level[e.to] == level[u] + 1 && e.cap > 0) {
                int tr = dfs(e.to, t, min(pushed, e.cap));
                if (tr > 0) {
                    e.cap -= tr;
                    G[e.to][e.rev].cap += tr;
                    return tr;
                }
            }
        }
        return 0;
    }
    int maxflow(int s, int t, int limit_flow = INT_MAX) {
        int flow = 0;
        while (flow < limit_flow && bfs(s,t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (flow < limit_flow) {
                int pushed = dfs(s, t, limit_flow - flow);
                if (pushed == 0) break;
                flow += pushed;
            }
        }
        return flow;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    int N = inf.readInt(3, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(2, 10000, "M");
    inf.readEoln();

    vector<tuple<int,int,int>> edges;
    edges.reserve(M);
    for (int i = 0; i < M; i++) {
        int P = inf.readInt(1, N, "P_i");
        inf.readSpace();
        int Q = inf.readInt(1, N, "Q_i");
        inf.readSpace();
        int L = inf.readInt(1, 35000, "L_i");
        inf.readEoln();
        ensuref(P != Q,
            "Self-loop detected on edge %d: (%d,%d)", i+1, P, Q);
        edges.emplace_back(P, Q, L);
    }

    // Build flow network to check existence of two edge-disjoint paths from 1 to N
    // We transform each undirected edge into a gadget with an intermediate node
    // so that using the edge in either direction consumes capacity 1.
    // Nodes: 1..N are original, for i in [0..M-1]:
    //   in-node = N + 2*i + 1
    //   out-node = N + 2*i + 2
    int totalNodes = N + 2*M;
    Dinic dinic(totalNodes);
    for (int i = 0; i < M; i++) {
        int u = get<0>(edges[i]);
        int v = get<1>(edges[i]);
        int inNode  = N + 2*i + 1;
        int outNode = N + 2*i + 2;
        // capacity 1 through the edge gadget
        dinic.addEdge(inNode, outNode, 1);
        // connect original nodes to gadget
        dinic.addEdge(u, inNode, 1);
        dinic.addEdge(v, inNode, 1);
        dinic.addEdge(outNode, u, 1);
        dinic.addEdge(outNode, v, 1);
    }

    // Compute max-flow from 1 to N, need at least 2 edge-disjoint paths
    int flow = dinic.maxflow(1, N, 2);
    ensuref(flow >= 2,
            "The graph does not allow two edge-disjoint paths between 1 and %d; flow=%d",
            N, flow);

    inf.readEof();
    return 0;
}
