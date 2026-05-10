#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and Q
    int N = inf.readInt(2, 50000, "N");
    inf.readSpace();
    int Q = inf.readInt(2, 50000, "Q");
    inf.readEoln();

    // 2. Read A_1..A_N (colors)
    vector<int> A = inf.readInts(N, 1, 50000, "A_i");
    inf.readEoln();

    // 3. Read P_1..P_N (permutation, P_0 = 0, P is permutation of 0..N)
    vector<int> P(N + 1, -1); // P[0..N]
    vector<int> P_input = inf.readInts(N, 0, N, "P_i");
    inf.readEoln();

    // Insert P_0 = 0 at front
    P[0] = 0;
    for (int i = 1; i <= N; ++i) {
        P[i] = P_input[i - 1];
    }

    // Check that P is a permutation of 0..N
    vector<bool> seen(N + 1, false);
    for (int i = 0; i <= N; ++i) {
        ensuref(P[i] >= 0 && P[i] <= N, "P[%d]=%d is not in range 0..N", i, P[i]);
        ensuref(!seen[P[i]], "P contains duplicate value %d at index %d", P[i], i);
        seen[P[i]] = true;
    }

    // 4. Read N-1 edges, check for valid tree
    vector<vector<int>> adj(N + 1); // 1-based
    set<pair<int, int>> edges;
    for (int i = 0; i < N - 1; ++i) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected at edge %d: (%d, %d)", i + 1, u, v);

        int a = min(u, v), b = max(u, v);
        ensuref(edges.count({a, b}) == 0, "Multiple edge detected between %d and %d", a, b);
        edges.insert({a, b});

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Check that the graph is connected and acyclic (i.e., a tree)
    vector<bool> visited(N + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    int visit_count = 1;
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int nxt : adj[cur]) {
            if (!visited[nxt]) {
                visited[nxt] = true;
                ++visit_count;
                q.push(nxt);
            }
        }
    }
    ensuref(visit_count == N, "The graph is not connected: only %d/%d nodes reachable from root", visit_count, N);

    // 5. Read Q queries
    int query1or2_count = 0;
    for (int i = 0; i < Q; ++i) {
        int type = inf.readInt(1, 3, "query_type");
        if (type == 1) {
            inf.readSpace();
            int x = inf.readInt(1, N, "x");
            inf.readEoln();
            ++query1or2_count;
        } else if (type == 2) {
            inf.readSpace();
            int x = inf.readInt(1, N, "x");
            inf.readSpace();
            int y = inf.readInt(1, N, "y");
            inf.readEoln();
            ++query1or2_count;
        } else if (type == 3) {
            inf.readSpace();
            int x = inf.readInt(1, N, "x");
            inf.readSpace();
            int z = inf.readInt(1, 50000, "z");
            inf.readEoln();
        } else {
            ensuref(false, "Invalid query type %d at query %d", type, i + 1);
        }
    }

    ensuref(query1or2_count >= 1, "There must be at least one query of type 1 or 2");

    inf.readEof();
}
