#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <set>
using namespace std;

const int MAX_V = 100;
const int MAX_M = 1000;
const int MAX_C = 10000;

typedef long long ll;
typedef pair<ll, int> pli;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int V = inf.readInt(2, MAX_V, "V");
    inf.readSpace();
    int M = inf.readInt(1, MAX_M, "M");
    inf.readEoln();

    // Read edges, check for constraints: 1 <= a, b <= V, 1 <= c <= 10000, no self-loops, no multi-edges
    vector<vector<pair<int, int>>> adj(V + 1); // 1-based
    set<pair<int, int>> edge_set;
    for (int i = 0; i < M; ++i) {
        int a = inf.readInt(1, V, "a");
        inf.readSpace();
        int b = inf.readInt(1, V, "b");
        inf.readSpace();
        int c = inf.readInt(1, MAX_C, "c");
        inf.readEoln();

        ensuref(a != b, "Self-loop detected at edge %d: (%d, %d)", i + 1, a, b);

        pair<int, int> e = minmax(a, b);
        ensuref(edge_set.count(e) == 0, "Multiple edge detected between %d and %d", a, b);
        edge_set.insert(e);

        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }

    int J = inf.readInt(1, V, "J");
    inf.readSpace();
    int S = inf.readInt(1, V, "S");
    inf.readEoln();

    ensuref(J != S, "Jiheon and Sungha cannot start at the same location: %d", J);

    // Check that J and S are not excluded from the graph (they are valid nodes)
    // (already checked by range)

    // Check that the graph is connected (since the statement says "지현이와 성하가 항상 만날 수 있는 입력만 주어진다.")
    // We'll do BFS from J and ensure all nodes are reachable
    vector<bool> vis(V + 1, false);
    queue<int> q;
    q.push(J);
    vis[J] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& p : adj[u]) {
            int v = p.first;
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= V; ++i) {
        ensuref(vis[i], "Graph is not connected: node %d is not reachable from Jiheon (%d)", i, J);
    }

    // Check that Sungha can also reach all nodes (not strictly necessary if graph is undirected and connected, but let's check)
    fill(vis.begin(), vis.end(), false);
    q.push(S);
    vis[S] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& p : adj[u]) {
            int v = p.first;
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= V; ++i) {
        ensuref(vis[i], "Graph is not connected: node %d is not reachable from Sungha (%d)", i, S);
    }

    // Check that for all nodes except J and S, there is at least one candidate node for meeting
    // But the statement says: "지현이와 성하가 항상 만날 수 있는 입력만 주어진다."
    // So, the input must be such that at least one node (other than J, S) is reachable from both.

    // Check that the answer always exists? No, the output can be -1 if no valid meeting place.
    // But the input must be such that "지현이와 성하가 항상 만날 수 있는 입력만 주어진다."
    // This means: the graph is connected, and there is a path from J to S (which is always true in a connected undirected graph).

    // Check for extra trailing whitespace or lines
    inf.readEof();
}
