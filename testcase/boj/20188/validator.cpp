#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(2, 300000, "N");
    inf.readEoln();

    // 2. Read N-1 edges
    vector<vector<int>> adj(N + 1); // 1-based
    set<pair<int, int>> edges;

    for (int i = 0; i < N - 1; ++i) {
        int a = inf.readInt(1, N, "a");
        inf.readSpace();
        int b = inf.readInt(1, N, "b");
        inf.readEoln();

        ensuref(a != b, "Loop detected at edge index %d: (%d, %d)", i + 1, a, b);

        int u = min(a, b), v = max(a, b);
        ensuref(!edges.count({u, v}), "Multiple edges detected at edge index %d: (%d, %d)", i + 1, a, b);
        edges.insert({u, v});

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // 3. Check connectivity (BFS from node 1)
    vector<bool> visited(N + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    int cnt = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
                ++cnt;
            }
        }
    }
    ensuref(cnt == N, "Graph is not connected: only %d out of %d nodes are reachable from node 1", cnt, N);

    // 4. Check that the graph is a tree (already checked: N-1 edges, connected, no multi-edges/loops)

    // 5. Check the "mountain" property:
    // "1번 오두막에서 다른 오두막으로 가는 가장 짧은 길을 따라 가면서 거치는 모든 오솔길들은 항상 산을 내려가는 방향이다."
    // That is, the tree is rooted at 1, and all edges are directed away from 1 (i.e., parent to child).
    // In other words, for any node, the unique path from 1 to node never goes "up" (never returns to parent).
    // This is always true for any tree rooted at 1, but let's check that the parent-child relation is well-defined.

    // Let's build parent array by BFS from 1
    vector<int> parent(N + 1, -1);
    vector<int> depth(N + 1, 0);
    queue<int> q2;
    q2.push(1);
    parent[1] = 0;
    depth[1] = 0;
    while (!q2.empty()) {
        int u = q2.front(); q2.pop();
        for (int v : adj[u]) {
            if (parent[v] == -1) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                q2.push(v);
            }
        }
    }
    // All nodes should have parent assigned (except 1)
    for (int i = 2; i <= N; ++i) {
        ensuref(parent[i] != -1, "Node %d is not reachable from node 1", i);
    }

    // 6. For Subtasks 1-3, check their specific constraints if possible
    // Subtask 1: path (chain)
    // Subtask 2: star
    // Subtask 3: binary tree with all leaves at same depth

    // We cannot know which subtask this input is for, so we do not enforce subtask-specific constraints.

    inf.readEof();
}
