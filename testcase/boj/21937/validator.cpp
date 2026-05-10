#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100000;
    const int MAX_M = 200000;

    int N = inf.readInt(1, MAX_N, "N");
    inf.readSpace();
    long long M = inf.readLong(0LL, 1LL * MAX_M, "M");
    inf.readEoln();

    // Upper bound from statement: M <= min(N*(N-1)/2, 200000)
    long long maxCompleteEdges = 1LL * N * (N - 1) / 2;
    ensuref(M <= maxCompleteEdges,
            "M=%lld exceeds N*(N-1)/2=%lld", M, maxCompleteEdges);

    vector<vector<int>> revAdj(N + 1);
    set<pair<int,int>> edges; // to ensure no duplicate (A,B)

    for (long long i = 0; i < M; ++i) {
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readEoln();

        ensuref(A != B, "Self-loop detected at edge index %lld: (%d, %d)", i, A, B);

        pair<int,int> e = {A, B};
        ensuref(!edges.count(e),
                "Duplicate edge detected at index %lld: (%d, %d)", i, A, B);
        edges.insert(e);

        // reverse graph: edges B -> A to traverse prerequisites of a task
        revAdj[B].push_back(A);
    }

    int X = inf.readInt(1, N, "X");
    inf.readEoln();

    // Problem states: "순서를 정할때 위배되는 작업 순서는 없다." -> graph is a DAG.
    // We must verify there is no directed cycle.
    // We'll do a DFS-based cycle detection on the forward graph (from A to B).
    // Since we stored only reverse edges, we reconstruct a forward adjacency
    // on the fly from the edge set.

    vector<vector<int>> adj(N + 1);
    adj.assign(N + 1, {});
    for (const auto &e : edges) {
        int A = e.first;
        int B = e.second;
        adj[A].push_back(B);
    }

    vector<int> color(N + 1, 0); // 0=unvisited,1=visiting,2=done
    bool hasCycle = false;

    function<void(int)> dfs = [&](int u) {
        color[u] = 1;
        for (int v : adj[u]) {
            if (color[v] == 0) {
                dfs(v);
                if (hasCycle) return;
            } else if (color[v] == 1) {
                hasCycle = true;
                return;
            }
        }
        color[u] = 2;
    };

    for (int i = 1; i <= N && !hasCycle; ++i) {
        if (color[i] == 0) dfs(i);
    }

    ensuref(!hasCycle, "Graph contains a directed cycle, but problem requires no contradictory order.");

    // Additionally, verify the "answer always exists" style property:
    // For any X, the number of prerequisites is finite in a DAG automatically,
    // so no extra reachability constraints are needed.

    inf.readEof();
}
