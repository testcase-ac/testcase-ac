#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read T
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // 2. Read K, M, P
        int K = inf.readInt(1, 10000, "K"); // No explicit bound, but let's be reasonable
        inf.readSpace();
        int M = inf.readInt(2, 1000, "M");
        inf.readSpace();
        int P = inf.readInt(1, M * (M - 1), "P"); // Directed, no self-loop, so at most M*(M-1)
        inf.readEoln();

        // 3. Read P edges, check constraints
        vector<vector<int>> adj(M + 1); // 1-based
        vector<int> indeg(M + 1, 0);
        set<pair<int, int>> edges;
        for (int i = 0; i < P; ++i) {
            int A = inf.readInt(1, M, "A");
            inf.readSpace();
            int B = inf.readInt(1, M, "B");
            inf.readEoln();

            ensuref(A != B, "Self-loop detected at edge %d: (%d, %d)", i + 1, A, B);
            ensuref(!edges.count({A, B}), "Multiple edge detected at edge %d: (%d, %d)", i + 1, A, B);
            edges.insert({A, B});
            adj[A].push_back(B);
            indeg[B]++;
        }

        // 4. Check that node M is the only sink (no outgoing edges)
        ensuref(adj[M].empty(), "Node M (%d) must not have outgoing edges", M);

        // 5. Check that node M is the only sink (no other node has outdegree 0)
        for (int v = 1; v <= M; ++v) {
            if (v == M) continue;
            ensuref(!adj[v].empty(), "Node %d is a sink (outdegree 0) but only node M (%d) can be a sink", v, M);
        }

        // 6. Check that the graph is a DAG (no cycles)
        // Kahn's algorithm
        vector<int> indeg_copy = indeg;
        queue<int> q;
        int cnt = 0;
        for (int v = 1; v <= M; ++v) {
            if (indeg_copy[v] == 0) q.push(v);
        }
        while (!q.empty()) {
            int v = q.front(); q.pop();
            cnt++;
            for (int u : adj[v]) {
                indeg_copy[u]--;
                if (indeg_copy[u] == 0) q.push(u);
            }
        }
        ensuref(cnt == M, "Graph is not a DAG (cycle detected), only %d/%d nodes can be topologically sorted", cnt, M);

        // 7. Check that node M is reachable from all sources (nodes with indegree 0)
        // (i.e., no disconnected components)
        vector<bool> vis(M + 1, false);
        queue<int> q2;
        for (int v = 1; v <= M; ++v) {
            if (indeg[v] == 0) {
                q2.push(v);
                vis[v] = true;
            }
        }
        while (!q2.empty()) {
            int v = q2.front(); q2.pop();
            for (int u : adj[v]) {
                if (!vis[u]) {
                    vis[u] = true;
                    q2.push(u);
                }
            }
        }
        ensuref(vis[M], "Node M (%d) is not reachable from any source", M);

        // 8. Check that all nodes are reachable from some source (i.e., no isolated nodes)
        for (int v = 1; v <= M; ++v) {
            ensuref(vis[v], "Node %d is not reachable from any source", v);
        }

        // 9. Check that there is at least one source (node with indegree 0)
        int source_cnt = 0;
        for (int v = 1; v <= M; ++v) {
            if (indeg[v] == 0) source_cnt++;
        }
        ensuref(source_cnt >= 1, "There must be at least one source (node with indegree 0)");

        // 10. Check that node M is not a source (since it is a sink)
        ensuref(indeg[M] >= 1, "Node M (%d) must not be a source (indegree 0)", M);

        // 11. Check that there are no isolated nodes (nodes with indegree 0 and outdegree 0)
        for (int v = 1; v <= M; ++v) {
            if (indeg[v] == 0 && adj[v].empty()) {
                ensuref(false, "Node %d is isolated (no incoming or outgoing edges)", v);
            }
        }

        // 12. Check that the Strahler order of node M is at most 12 (Amazon) or 10 (Mississippi) as per description?
        // No, this is just a fun fact, not a constraint.

        // 13. Each test case must end with exactly one newline (already enforced by readEoln after each edge)
    }

    inf.readEof();
}
