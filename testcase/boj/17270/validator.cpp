#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

const int MAX_V = 100;
const int MAX_M = 1000;
const int MAX_C = 10000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int V = inf.readInt(2, MAX_V, "V");
    inf.readSpace();
    int M = inf.readInt(1, MAX_M, "M");
    inf.readEoln();

    vector<vector<int>> adj(V + 1);
    for (int i = 0; i < M; ++i) {
        int a = inf.readInt(1, V, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, V, "b_i");
        inf.readSpace();
        inf.readInt(1, MAX_C, "c_i");
        inf.readEoln();

        // CHECK: the statement does not forbid self-loops or parallel roads.
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int J = inf.readInt(1, V, "J");
    inf.readSpace();
    int S = inf.readInt(1, V, "S");
    inf.readEoln();

    // CHECK: the statement says Jiheon and Sungha can always meet, but does
    // not require every place in the graph to be connected.
    vector<bool> vis(V + 1, false);
    queue<int> q;
    q.push(J);
    vis[J] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    ensuref(vis[S], "J and S must be connected: J=%d S=%d", J, S);

    inf.readEof();
}
