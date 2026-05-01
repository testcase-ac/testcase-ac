#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N, M, X, Y
    int N = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int M = inf.readInt(0, 500000, "M");
    inf.readSpace();
    int X = inf.readInt(1, N, "X");
    inf.readSpace();
    int Y = inf.readInt(1, N, "Y");
    inf.readEoln();

    // A_i
    vector<long long> A(N + 1);
    for (int i = 1; i <= N; ++i) {
        A[i] = inf.readLong(0LL, 500000LL, "A_i");
        if (i != N) inf.readSpace();
    }
    inf.readEoln();

    // Edges, no loops, no multi-edges (undirected)
    vector<vector<int>> adj(N + 1);
    set<pair<int,int>> edges;
    for (int i = 0; i < M; ++i) {
        int u = inf.readInt(1, N, "S_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "E_i");
        inf.readEoln();

        ensuref(u != v, "Loop detected at edge %d: (%d, %d)", i + 1, u, v);
        int a = min(u, v), b = max(u, v);
        ensuref(!edges.count({a, b}),
                "Multiple edge detected at edge %d: (%d, %d)", i + 1, u, v);
        edges.insert({a, b});

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // B_i: distinct, in range
    vector<int> B(Y);
    vector<int> markB(N + 1, 0);
    for (int i = 0; i < Y; ++i) {
        B[i] = inf.readInt(1, N, "B_i");
        if (i != Y - 1) inf.readSpace();
        ensuref(!markB[B[i]], "B_i values must be distinct, duplicate %d at index %d",
                B[i], i + 1);
        markB[B[i]] = 1;
    }
    inf.readEoln();

    // ----- Global semantic checks -----
    // 1) Simulate security propagation and ensure nobody is unprotected forever (else answer is -1).
    //    Nodes with infinite safe time must not exist.
    const long long INF = (long long)4e18;
    vector<long long> dist(N + 1, INF);

    // Multi-source BFS from security start nodes
    queue<int> q;
    for (int b : B) {
        dist[b] = 0;
        q.push(b);
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    // If any node has dist == INF, it is never secured -> infinite money achievable.
    // But that depends on X and A_i: if X >= 1 and A_i > 0, we can get infinite money.
    // Problem guarantees: if infinite money can be obtained, correct output is -1.
    // From validator perspective, this must NOT happen (except if problem setter
    // indeed wants such cases). The statement: "만약 무한히 많은 돈을 얻을 수 있다면 대신 -1을 출력한다."
    // doesn't say it never happens, so we must ALLOW such inputs.
    // Thus: we only validate consistency of propagation, not "no infinite" property.
    // There is no contradiction we can easily check here; propagation is by definition
    // what we simulated, starting time 0.5 then +1 per hop, but no impossible scenario.

    // We still check that BFS ran correctly for all nodes (always true) and dist >= 0.
    for (int i = 1; i <= N; ++i) {
        ensuref(dist[i] >= 0 || dist[i] == INF,
                "Internal BFS distance negative at node %d", i);
    }

    // No extra structural constraints like connectivity are stated, so no further checks.

    inf.readEof();
}
