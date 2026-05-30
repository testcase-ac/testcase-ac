#include "testlib.h"
#include <queue>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    vector<vector<int>> adj(n + 1);

    for (int i = 1; i <= m; i++) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        inf.readInt(0, 99999, "w_i");
        inf.readEoln();

        adj[u].push_back(v);
    }

    int A = inf.readInt(1, n, "src");
    inf.readSpace();
    int B = inf.readInt(1, n, "dst");
    inf.readEoln();

    vector<char> seen(n + 1, 0);
    queue<int> q;
    seen[A] = 1;
    q.push(A);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!seen[v]) {
                seen[v] = 1;
                q.push(v);
            }
        }
    }
    ensuref(seen[B], "No path from src=%d to dst=%d", A, B);

    inf.readEof();
    return 0;
}
