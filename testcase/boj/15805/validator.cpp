#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Reconstruct tree from traversal and check all guarantees.
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 200000;

    int N = inf.readInt(1, MAXN, "N");
    inf.readEoln();

    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        A[i] = inf.readInt(0, INT_MAX, "A_i");
        if (i + 1 < N) inf.readSpace();
    }
    inf.readEoln();

    // --- Basic checks on node indices and existence of root 0 ---
    // All city indices must be contiguous from 0..K-1 (for some K).
    // First, get max and min.
    int mn = A[0], mx = A[0];
    for (int x : A) {
        mn = min(mn, x);
        mx = max(mx, x);
    }
    ensuref(mn == 0, "Minimum node index must be 0, but got %d", mn);

    int K = mx + 1;
    ensuref(K >= 1, "There must be at least one city");

    // Check all indices are in [0, K-1] (this is implied, but we had INT_MAX as upper bound).
    for (int i = 0; i < N; ++i) {
        ensuref(0 <= A[i] && A[i] < K, "A[%d] = %d is out of range [0, %d]", i, A[i], K-1);
    }

    // Check all nodes 0..K-1 actually appear.
    vector<int> freq(K, 0);
    for (int x : A) freq[x]++;
    for (int v = 0; v < K; ++v) {
        ensuref(freq[v] > 0, "Node %d does not appear in traversal", v);
    }

    // --- Check traversal corresponds to a valid tree tour from root 0 ---
    // Conditions inferred from statement:
    // 1) Tour starts at root 0.
    // 2) Consecutive cities are equal or adjacent in the (unknown) tree.
    // 3) Tour is some DFS-like minimal visit of all cities (not needed to validate).
    // 4) There exists a tree realizing this traversal; we must *verify* such tree exists.

    // The tour must start and end at root 0 (since it starts from root and "comes back").
    ensuref(A[0] == 0, "Traversal must start at root 0, but A[0] = %d", A[0]);
    ensuref(A[N - 1] == 0, "Traversal must end at root 0, but A[N-1] = %d", A[N - 1]);

    // Reconstruct parent using a stack that simulates moving along tree edges.
    // When we go from current node u to next node v:
    // - If v is new: set parent[v] = u.
    // - Else: we must be moving along existing edges.
    vector<int> parent(K, -2); // -2: unvisited, -1: root
    vector<vector<int>> adj(K);

    parent[0] = -1; // root
    int cur = A[0];
    for (int i = 1; i < N; ++i) {
        int nxt = A[i];
        int u = cur, v = nxt;

        if (u == v) {
            // Staying in the same city: always allowed.
            cur = v;
            continue;
        }

        // If v not yet seen, we must create a new edge u-v and set parent.
        if (parent[v] == -2) {
            parent[v] = u;
            // add undirected edge
            adj[u].push_back(v);
            adj[v].push_back(u);
            cur = v;
            continue;
        }

        // v already has a parent; then we must be walking along an existing edge.
        // That implies (u, v) is an existing edge, i.e., parent relationship or reverse.
        bool ok = false;
        if (parent[v] == u || parent[u] == v) ok = true;
        else {
            // Could still be an already-built edge between siblings, but that cannot
            // occur in a tree (no extra edges). So only parent-child moves allowed.
            ok = false;
        }
        ensuref(ok, "Invalid move between already discovered nodes at step %d: %d -> %d",
                i, u, v);

        // No need to add edges; they must already be in adj if we want to verify consistency.
        // However, to be defensive, check that edge exists in adj.
        bool found = false;
        for (int to : adj[u]) if (to == v) { found = true; break; }
        ensuref(found, "Move %d -> %d at step %d not present in constructed tree",
                u, v, i);

        cur = v;
    }

    // Ensure all nodes have assigned parent (i.e., traversal reached them).
    for (int v = 0; v < K; ++v) {
        ensuref(parent[v] != -2, "Node %d never assigned a parent (unreached)", v);
    }

    // --- Global tree validity checks ---
    // 1) Exactly one root (parent -1), and it must be node 0.
    int rootCount = 0;
    for (int v = 0; v < K; ++v) {
        if (parent[v] == -1) {
            ++rootCount;
            ensuref(v == 0, "Only node 0 may have no parent, but node %d has parent -1", v);
        } else {
            ensuref(0 <= parent[v] && parent[v] < K,
                    "Invalid parent index for node %d: %d", v, parent[v]);
        }
    }
    ensuref(rootCount == 1, "There must be exactly one root, but found %d", rootCount);

    // 2) Build adjacency from parents and check it's a tree: K-1 edges and connected, no cycles.
    vector<vector<int>> g(K);
    int edges = 0;
    for (int v = 0; v < K; ++v) {
        if (parent[v] >= 0) {
            int p = parent[v];
            g[p].push_back(v);
            g[v].push_back(p);
            ++edges;
        }
    }
    ensuref(edges == K - 1, "Number of edges must be K-1 = %d, but got %d", K - 1, edges);

    // Connectivity and no cycles via BFS from root 0.
    vector<int> vis(K, 0);
    queue<int> q;
    q.push(0);
    vis[0] = 1;
    int cnt = 0;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        ++cnt;
        for (int to : g[v]) {
            if (!vis[to]) {
                vis[to] = 1;
                q.push(to);
            }
        }
    }
    ensuref(cnt == K, "Tree must be connected, but only %d/%d nodes reachable from root", cnt, K);

    inf.readEof();
}
