#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M
    int N = inf.readInt(2, 300000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 300000, "M");
    inf.readEoln();

    // 2. Read edges, check constraints: 1 <= u,v <= N, u != v, no multi-edges, undirected
    set<pair<int,int>> edges;
    vector<vector<int>> adj(N+1); // 1-based

    for (int i = 0; i < M; ++i) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected at edge %d: (%d, %d)", i+1, u, v);

        int a = min(u, v), b = max(u, v);
        ensuref(!edges.count({a, b}), "Multiple edge detected between %d and %d at edge %d", u, v, i+1);
        edges.insert({a, b});

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 3. Check connectivity: BFS/DFS from node 1, all nodes must be reachable
    vector<bool> vis(N+1, false);
    queue<int> q;
    q.push(1);
    vis[1] = true;
    int cnt = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
                ++cnt;
            }
        }
    }
    ensuref(cnt == N, "Graph is not connected: only %d/%d nodes reachable from node 1", cnt, N);

    // 4. Check that there is at least one cycle (i.e., "반복적으로 도는 방법이 적어도 하나는 있다는 것이 보장된다")
    // This is implied by the problem, but as a validator, we must check it.
    // In a connected undirected graph, a cycle exists iff M >= N.
    // But let's check for a cycle explicitly (DFS, find a back edge).
    vector<bool> visited(N+1, false);
    bool found_cycle = false;
    function<void(int,int)> dfs = [&](int u, int parent) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (v == parent) continue;
            if (visited[v]) {
                found_cycle = true;
                return;
            } else {
                dfs(v, u);
                if (found_cycle) return;
            }
        }
    };
    dfs(1, -1);
    ensuref(found_cycle, "No cycle found in the graph, but problem guarantees at least one cycle");

    // 5. Each edge must be between two different nodes, and at most one edge per pair (already checked above)

    // 6. Each line ends with EOLN, and file ends with EOF
    inf.readEof();
}
