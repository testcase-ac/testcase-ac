#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of nodes
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Track which node IDs have been seen on the leftmost column
    vector<bool> seen(N+1, false);
    // Track parent of each node; -1 means no parent yet
    vector<int> parent(N+1, -1);
    // Adjacency list of children for connectivity check
    vector<vector<int>> children(N+1);
    // Count edges (non -1 children)
    int edgeCount = 0;

    // Read node definitions
    for (int i = 0; i < N; i++) {
        int u = inf.readInt(1, N, "node");
        inf.readSpace();
        int l = inf.readInt(-1, N, "left");
        inf.readSpace();
        int r = inf.readInt(-1, N, "right");
        inf.readEoln();

        // Each node index must appear exactly once
        ensuref(!seen[u], "Node %d appears more than once", u);
        seen[u] = true;

        // Process left child
        if (l != -1) {
            // Range and self-loop check
            ensuref(1 <= l && l <= N, "Left child %d of node %d out of range", l, u);
            ensuref(l != u, "Node %d has itself as left child", u);
            // Multi-parent check
            ensuref(parent[l] == -1,
                    "Node %d has more than one parent: %d and %d",
                    l, parent[l], u);
            parent[l] = u;
            children[u].push_back(l);
            edgeCount++;
        }
        // Process right child
        if (r != -1) {
            ensuref(1 <= r && r <= N, "Right child %d of node %d out of range", r, u);
            ensuref(r != u, "Node %d has itself as right child", u);
            ensuref(parent[r] == -1,
                    "Node %d has more than one parent: %d and %d",
                    r, parent[r], u);
            parent[r] = u;
            children[u].push_back(r);
            edgeCount++;
        }
    }

    // Every node ID 1..N must appear exactly once
    for (int i = 1; i <= N; i++) {
        ensuref(seen[i], "Node %d is missing from input", i);
    }

    // There must be exactly one root (node with no parent)
    vector<int> roots;
    for (int i = 1; i <= N; i++) {
        if (parent[i] == -1) roots.push_back(i);
    }
    ensuref(roots.size() == 1,
            "There must be exactly one root, found %d", (int)roots.size());
    int root = roots[0];

    // A valid tree with N nodes must have exactly N-1 edges
    ensuref(edgeCount == N-1,
            "Number of edges is %d but should be %d", edgeCount, N-1);

    // Check connectivity: all nodes reachable from the root
    vector<bool> visited(N+1, false);
    queue<int> q;
    visited[root] = true;
    q.push(root);
    int visitCount = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : children[u]) {
            if (!visited[v]) {
                visited[v] = true;
                visitCount++;
                q.push(v);
            }
        }
    }
    ensuref(visitCount == N,
            "The tree is not connected: only %d out of %d nodes are reachable from root %d",
            visitCount, N, root);

    inf.readEof();
    return 0;
}
