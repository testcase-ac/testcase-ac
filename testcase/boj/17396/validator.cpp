#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int w;
};

const long long INF = (1LL << 62);

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 300000, "M");
    inf.readEoln();

    vector<int> vis(N);
    for (int i = 0; i < N; ++i) {
        vis[i] = inf.readInt(0, 1, "a_i");
        if (i + 1 < N) inf.readSpace();
    }
    inf.readEoln();

    ensuref(vis[0] == 0, "a_0 must be 0 (start is not visible)");
    ensuref(vis[N - 1] == 1, "a_{N-1} must be 1 (nexus is visible)");

    vector<vector<Edge>> g(N);
    set<pair<int,int>> edges;

    for (int i = 0; i < M; ++i) {
        int a = inf.readInt(0, N - 1, "a");
        inf.readSpace();
        int b = inf.readInt(0, N - 1, "b");
        inf.readSpace();
        int t = inf.readInt(1, 100000, "t");
        inf.readEoln();

        ensuref(a != b, "Self-loop detected at edge %d: (%d, %d)", i, a, b);
        pair<int,int> e1 = {a, b};
        pair<int,int> e2 = {b, a};
        ensuref(!edges.count(e1), "Multiple edge detected between %d and %d", a, b);
        ensuref(!edges.count(e2), "Multiple edge detected between %d and %d", a, b);
        edges.insert(e1);
        edges.insert(e2);

        g[a].push_back({b, t});
        g[b].push_back({a, t});
    }

    // Global property: input guarantees that only nodes with vis==0 are passable,
    // except N-1 which is allowed even with vis==1. We must ensure that
    // any path from 0 to N-1 that uses only allowed nodes exists iff the
    // correct answer (shortest such path) equals what solutions will output.
    // The statement only guarantees "if cannot reach then answer is -1".
    // There's no extra promise like "answer always <= X", so no extra global
    // condition must be enforced. However, we should still verify that the
    // graph and constraints are consistent with intended rules by simulating
    // the allowed-movement shortest path and checking that costs don't overflow.

    // Dijkstra restricted to allowed nodes:
    vector<long long> dist(N, INF);
    using P = pair<long long,int>;
    priority_queue<P, vector<P>, greater<P>> pq;

    dist[0] = 0;
    pq.push({0, 0});

    auto allowed = [&](int v) -> bool {
        if (v == 0) return true;
        if (v == N - 1) return true;
        return vis[v] == 0;
    };

    while (!pq.empty()) {
        auto [cd, v] = pq.top();
        pq.pop();
        if (cd != dist[v]) continue;
        if (cd > INF / 2) break;
        for (auto &e : g[v]) {
            int to = e.to;
            int w = e.w;
            if (!allowed(to)) continue;
            long long nd = cd + w;
            ensuref(nd >= 0 && nd < INF,
                    "Distance overflow while relaxing edge (%d,%d) with weight %d", v, to, w);
            if (nd < dist[to]) {
                dist[to] = nd;
                pq.push({nd, to});
            }
        }
    }

    // No specific required property on existence; just ensure computation finished.

    inf.readEof();
}
