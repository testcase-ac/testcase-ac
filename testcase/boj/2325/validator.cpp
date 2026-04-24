#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static const int MAXZ = 1000;

int N, M;
vector<vector<pair<int,int>>> adj;
vector<int> X, Y, Z;
vector<char> mat_edge;
vector<int> tin, low;
vector<char> isBridge, visitedDFS;
int timerDFS;

void dfs_bridges(int u, int pe) {
    visitedDFS[u] = 1;
    tin[u] = low[u] = timerDFS++;
    for (auto &pr : adj[u]) {
        int v = pr.first;
        int id = pr.second;
        if (id == pe) continue;
        if (visitedDFS[v]) {
            // back-edge
            low[u] = min(low[u], tin[v]);
        } else {
            dfs_bridges(v, id);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) {
                isBridge[id] = 1;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int maxM = (long long)N * (N - 1) / 2;
    M = inf.readInt(1, maxM, "M");
    inf.readEoln();

    // Prepare storage
    X.resize(M);
    Y.resize(M);
    Z.resize(M);
    adj.assign(N+1, {});
    mat_edge.assign((N+1)*(N+1), 0);

    // Read edges
    for (int i = 0; i < M; i++) {
        int x = inf.readInt(1, N, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, N, "y_i");
        inf.readSpace();
        int z = inf.readInt(1, MAXZ, "z_i");
        inf.readEoln();

        // no loops
        ensuref(x != y, "Edge %d is a loop: (%d,%d)", i, x, y);

        // no multi-edges
        int u = min(x, y), v = max(x, y);
        if (mat_edge[u*(N+1) + v]) {
            ensuref(false, "Multiple edge between %d and %d at index %d", u, v, i);
        }
        mat_edge[u*(N+1) + v] = 1;

        X[i] = x;
        Y[i] = y;
        Z[i] = z;
        // build adjacency list
        adj[x].push_back({y, i});
        adj[y].push_back({x, i});
    }

    // Check initial connectivity from 1 to N
    {
        vector<char> vis(N+1, 0);
        queue<int> q;
        q.push(1);
        vis[1] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &pr : adj[u]) {
                int v = pr.first;
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
        ensuref(vis[N], "Node %d is not reachable from node 1 in the initial graph", N);
    }

    // Find bridges in the component of 1
    tin.assign(N+1, -1);
    low.assign(N+1, 0);
    visitedDFS.assign(N+1, 0);
    isBridge.assign(M, 0);
    timerDFS = 0;
    dfs_bridges(1, -1);

    // For each bridge, ensure removing it still leaves 1->N reachable
    for (int bid = 0; bid < M; bid++) {
        if (!isBridge[bid]) continue;
        // BFS skipping edge bid
        vector<char> vis(N+1, 0);
        queue<int> q;
        vis[1] = 1;
        q.push(1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &pr : adj[u]) {
                int v = pr.first, id = pr.second;
                if (id == bid) continue;
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
        if (!vis[N]) {
            ensuref(false,
                    "Edge %d (%d,%d) is a bridge whose removal disconnects 1 and %d",
                    bid, X[bid], Y[bid], N);
        }
    }

    inf.readEof();
    return 0;
}
