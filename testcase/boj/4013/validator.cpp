#include "testlib.h"
#include <vector>
#include <queue>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int M = inf.readInt(0, 500000, "M");
    inf.readEoln();

    // Read directed edges
    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();
        adj[u].push_back(v);
    }

    // Read ATM cash at each node
    vector<int> cash(N + 1);
    for (int i = 1; i <= N; i++) {
        cash[i] = inf.readInt(0, 4000, "cash_i");
        inf.readEoln();
    }

    // Read start S and number of restaurants P
    int S = inf.readInt(1, N, "S");
    inf.readSpace();
    int P = inf.readInt(1, N, "P");
    // P must be at most N (already ensured by readInt upper bound)
    inf.readEoln();

    // Read restaurant node list
    vector<int> rest = inf.readInts(P, 1, N, "restaurant");
    inf.readEoln();

    // Check that at least one restaurant is reachable from S
    vector<char> vis(N + 1, false);
    queue<int> q;
    vis[S] = true;
    q.push(S);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    bool any = false;
    for (int x : rest) {
        if (vis[x]) {
            any = true;
            break;
        }
    }
    ensuref(any, "No reachable restaurant from S=%d", S);

    inf.readEof();
    return 0;
}
