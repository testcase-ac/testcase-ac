#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, R
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int R = inf.readInt(1, N, "R");
    inf.readEoln();

    // 2. Read N-1 edges, build adjacency list, check for simple undirected tree
    vector<vector<int>> adj(N+1);
    set<pair<int,int>> edges;
    for (int i = 0; i < N-1; ++i) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected at edge %d: (%d, %d)", i+1, u, v);
        int a = min(u, v), b = max(u, v);
        ensuref(!edges.count({a, b}), "Multiple edge detected at edge %d: (%d, %d)", i+1, u, v);
        edges.insert({a, b});
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 3. Check tree is connected and acyclic (BFS from R)
    vector<bool> visited(N+1, false);
    queue<int> q;
    q.push(R);
    visited[R] = true;
    int visit_cnt = 1;
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int nxt : adj[cur]) {
            if (!visited[nxt]) {
                visited[nxt] = true;
                ++visit_cnt;
                q.push(nxt);
            }
        }
    }
    ensuref(visit_cnt == N, "Tree is not connected from root %d: only %d/%d nodes reachable", R, visit_cnt, N);

    // 4. Read L, leaf nodes and their values
    int L = inf.readInt(1, N, "L");
    inf.readEoln();

    set<int> leaf_nodes;
    map<int, int> leaf_values;
    for (int i = 0; i < L; ++i) {
        int k = inf.readInt(1, N, "k_i");
        inf.readSpace();
        int t = inf.readInt(0, 1000000000, "t_i");
        inf.readEoln();

        ensuref(!leaf_nodes.count(k), "Duplicate leaf node in leaf list at line %d: node %d", i+1, k);
        leaf_nodes.insert(k);
        leaf_values[k] = t;
    }

    // 5. Check that the set of leaf nodes matches the actual leaves in the tree
    // Find leaves in the tree (degree 1, except possibly root)
    set<int> actual_leaves;
    for (int i = 1; i <= N; ++i) {
        int deg = adj[i].size();
        if (i == R) {
            if (deg == 0) actual_leaves.insert(i); // root is a single node
        } else {
            if (deg == 1) actual_leaves.insert(i);
        }
    }
    ensuref(leaf_nodes == actual_leaves,
        "Leaf nodes in input do not match actual tree leaves. Input leaves: %zu, actual leaves: %zu",
        leaf_nodes.size(), actual_leaves.size());

    ensuref((int)leaf_nodes.size() == L, "L=%d but number of unique leaf nodes is %zu", L, leaf_nodes.size());

    // 6. Read Q, and Q queries
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 0; i < Q; ++i) {
        int qv = inf.readInt(1, N, "q_i");
        inf.readEoln();
    }

    inf.readEof();
}
