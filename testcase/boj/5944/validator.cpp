#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: C, P, PB, PA1, PA2
    int C = inf.readInt(1, 200000, "C");
    inf.readSpace();
    int P = inf.readInt(1, 100000, "P");
    inf.readSpace();
    int PB = inf.readInt(1, P, "PB");
    inf.readSpace();
    int PA1 = inf.readInt(1, P, "PA1");
    inf.readSpace();
    int PA2 = inf.readInt(1, P, "PA2");
    inf.readEoln();

    // All three of these pastures are distinct
    ensuref(PB != PA1 && PB != PA2 && PA1 != PA2,
        "PB, PA1, and PA2 must be distinct: PB=%d, PA1=%d, PA2=%d", PB, PA1, PA2);

    // Read edges
    vector<vector<pair<int, int>>> adj(P + 1); // 1-based
    long long sum_D = 0;
    for (int i = 0; i < C; ++i) {
        int P1 = inf.readInt(1, P, "P1_i");
        inf.readSpace();
        int P2 = inf.readInt(1, P, "P2_i");
        inf.readSpace();
        int D = inf.readInt(1, 2000000000, "D_i");
        inf.readEoln();

        ensuref(P1 != P2, "Cowpath leads from a pasture to itself at line %d: (%d, %d)", i + 2, P1, P2);

        adj[P1].emplace_back(P2, D);
        adj[P2].emplace_back(P1, D);

        sum_D += D;
        ensuref(sum_D <= 2000000000LL, "Sum of all D_i exceeds 2,000,000,000 after line %d", i + 2);
    }

    // Check that the graph is connected
    vector<bool> vis(P + 1, false);
    queue<int> q;
    q.push(1);
    vis[1] = true;
    int seen = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &e : adj[u]) {
            int v = e.first;
            if (!vis[v]) {
                vis[v] = true;
                ++seen;
                q.push(v);
            }
        }
    }
    ensuref(seen == P, "Graph is not connected: only %d out of %d pastures are reachable", seen, P);

    inf.readEof();
}
