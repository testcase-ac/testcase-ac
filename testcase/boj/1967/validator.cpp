#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of nodes
    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();
    
    // Prepare for parent checks, edge storage, adjacency
    vector<bool> hasParent(n+1, false);
    set<pair<int,int>> directedEdges;
    vector<vector<int>> adj(n+1);
    
    int prevU = -1, prevV = -1;
    // Read n-1 edges
    for (int i = 0; i < n - 1; i++) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int w = inf.readInt(1, 100, "w_i");
        inf.readEoln();
        
        // No loops
        ensuref(u != v,
            "Loop detected at edge index %d: parent and child both %d", i, u);
        // Root cannot be a child
        ensuref(v != 1,
            "Root node 1 cannot appear as a child (found at edge index %d)", i);
        // Each node except root has exactly one parent
        ensuref(!hasParent[v],
            "Node %d has multiple parents (detected at edge index %d)", v, i);
        hasParent[v] = true;
        
        // No duplicate edges
        ensuref(!directedEdges.count({u, v}),
            "Duplicate edge detected: (%d, %d) at edge index %d", u, v, i);
        directedEdges.insert({u, v});
        
        // Input ordering: by parent asc, then child asc
        if (i > 0) {
            ensuref(prevU < u || (prevU == u && prevV < v),
                "Edges not in required sorted order at index %d: got (%d,%d) after (%d,%d)",
                i, u, v, prevU, prevV);
        }
        prevU = u; prevV = v;
        
        // Build undirected adjacency for connectivity check
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // All nodes except root must have exactly one parent
    if (n > 1) {
        int cntParents = 0;
        for (int i = 1; i <= n; i++) {
            if (i == 1) {
                ensuref(!hasParent[i],
                    "Root node 1 should not have a parent");
            } else {
                if (hasParent[i]) cntParents++;
            }
        }
        ensuref(cntParents == n - 1,
            "Expected %d parent links, found %d", n-1, cntParents);
    }

    // Check connectivity via BFS from root = 1
    {
        vector<char> vis(n+1, 0);
        queue<int> q;
        vis[1] = 1;
        q.push(1);
        int seen = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (!vis[v]) {
                    vis[v] = 1;
                    seen++;
                    q.push(v);
                }
            }
        }
        ensuref(seen == n,
            "Tree is not connected: only %d out of %d nodes reachable from root", seen, n);
    }

    inf.readEof();
    return 0;
}
