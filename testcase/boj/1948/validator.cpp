#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of cities n and roads m
    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    // Prepare storage for graph
    vector<vector<pair<int,int>>> adj(n+1), revadj(n+1);
    vector<int> indegree(n+1, 0), outdegree(n+1, 0);

    // Read edges
    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int w = inf.readInt(1, 10000, "w_i");
        inf.readEoln();

        // No self-loop (would be a cycle)
        ensuref(u != v, "Loop detected on edge %d: from %d to %d", i, u, v);

        // Build graph
        adj[u].push_back({v, w});
        revadj[v].push_back({u, w});
        indegree[v]++;
        outdegree[u]++;
    }

    // Read start and end cities
    int s = inf.readInt(1, n, "s");
    inf.readSpace();
    int t = inf.readInt(1, n, "t");
    inf.readEoln();

    // Start city should have zero in-degree
    ensuref(indegree[s] == 0, "Start city %d has incoming roads", s);
    // End city should have zero out-degree
    ensuref(outdegree[t] == 0, "End city %d has outgoing roads", t);

    // Check that every city is reachable from start (forward BFS)
    vector<char> vis(n+1, 0);
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    int cnt_vis = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &e : adj[u]) {
            int v = e.first;
            if (!vis[v]) {
                vis[v] = 1;
                cnt_vis++;
                q.push(v);
            }
        }
    }
    ensuref(cnt_vis == n, "City %d is unreachable from start %d", 
            [&](){
                for (int i = 1; i <= n; i++)
                    if (!vis[i]) return i;
                return 1;
            }(), s);

    // Check that every city can reach end (reverse BFS)
    fill(vis.begin(), vis.end(), 0);
    q.push(t);
    vis[t] = 1;
    cnt_vis = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &e : revadj[u]) {
            int v = e.first;
            if (!vis[v]) {
                vis[v] = 1;
                cnt_vis++;
                q.push(v);
            }
        }
    }
    ensuref(cnt_vis == n, "City %d cannot reach end %d", 
            [&](){
                for (int i = 1; i <= n; i++)
                    if (!vis[i]) return i;
                return 1;
            }(), t);

    // Check acyclicity via Kahn's algorithm
    vector<int> indeg_copy = indegree;
    queue<int> kahn;
    for (int i = 1; i <= n; i++) {
        if (indeg_copy[i] == 0)
            kahn.push(i);
    }
    int topo_cnt = 0;
    while (!kahn.empty()) {
        int u = kahn.front(); kahn.pop();
        topo_cnt++;
        for (auto &e : adj[u]) {
            int v = e.first;
            indeg_copy[v]--;
            if (indeg_copy[v] == 0)
                kahn.push(v);
        }
    }
    ensuref(topo_cnt == n, "Graph contains a cycle");

    inf.readEof();
    return 0;
}
