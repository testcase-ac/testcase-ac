#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;
    const int MAXD = 10000;
    const long long MAXS = 1000000000LL;
    const long long MAXV = 1000000000LL;

    int N = inf.readInt(3, MAXN, "N");
    inf.readEoln();

    // Read tree edges
    vector<vector<int>> adj(N + 1);
    vector<int> deg(N + 1, 0);

    for (int i = 0; i < N - 1; ++i) {
        int U = inf.readInt(1, N, "U");
        inf.readSpace();
        int V = inf.readInt(1, N, "V");
        inf.readSpace();
        int D = inf.readInt(1, MAXD, "D");
        inf.readEoln();

        ensuref(U != V, "Self loop detected at edge %d: (%d, %d)", i, U, V);

        adj[U].push_back(V);
        adj[V].push_back(U);
        deg[U]++;
        deg[V]++;
    }

    // Check connectivity (tree property) via BFS from 1
    vector<int> q(N + 1);
    vector<char> vis(N + 1, 0);
    int head = 0, tail = 0;
    q[tail++] = 1;
    vis[1] = 1;
    int seen = 1;

    while (head < tail) {
        int u = q[head++];
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                q[tail++] = v;
                ++seen;
            }
        }
    }

    ensuref(seen == N,
            "Graph is not connected: reachable %d out of %d nodes from capital (1)",
            seen, N);

    // Read messengers data for cities 2..N
    for (int i = 2; i <= N; ++i) {
        long long S = inf.readLong(0LL, MAXS, "S_i");
        inf.readSpace();
        long long V = inf.readLong(1LL, MAXV, "V_i");
        inf.readEoln();
        (void)S;
        (void)V;
    }

    inf.readEof();
}
