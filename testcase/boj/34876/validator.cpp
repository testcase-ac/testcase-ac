#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, K
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100, "K");
    inf.readEoln();

    // 2. Read s_1 ... s_N
    vector<int> s(N+1, 0); // s[1..N], s[0] is not used
    for (int i = 1; i <= N; ++i) {
        s[i] = inf.readInt(0, 100, ("s_" + to_string(i)).c_str());
        if (i < N) inf.readSpace();
    }
    inf.readEoln();

    // 3. Read N edges
    // The graph has N+1 nodes (0..N), and N edges
    vector<vector<pair<int,int>>> adj(N+1); // adj[u] = vector of {v, T}
    set<pair<int,int>> edges_seen;
    for (int i = 0; i < N; ++i) {
        int A = inf.readInt(0, N, "A");
        inf.readSpace();
        int B = inf.readInt(0, N, "B");
        inf.readSpace();
        int T = inf.readInt(1, 100, "T");
        inf.readEoln();

        ensuref(A != B, "Self-loop detected at edge %d: (%d, %d)", i+1, A, B);
        ensuref(edges_seen.count({A,B}) == 0 && edges_seen.count({B,A}) == 0,
            "Multiple edge detected between %d and %d at edge %d", A, B, i+1);
        edges_seen.insert({A,B});
        edges_seen.insert({B,A});

        adj[A].emplace_back(B, T);
        adj[B].emplace_back(A, T);
    }

    // 4. Check that the graph is a tree: connected and acyclic
    // Since N+1 nodes and N edges, only need to check connectivity
    vector<bool> visited(N+1, false);
    queue<int> q;
    q.push(0);
    visited[0] = true;
    int vis_cnt = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &p : adj[u]) {
            int v = p.first;
            if (!visited[v]) {
                visited[v] = true;
                ++vis_cnt;
                q.push(v);
            }
        }
    }
    ensuref(vis_cnt == N+1, "Graph is not connected: only %d of %d nodes reachable from 0", vis_cnt, N+1);

    inf.readEof();
}
