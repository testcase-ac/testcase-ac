#include "testlib.h"
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of people / countries
    int p = inf.readInt(1, 3, "p");
    inf.readEoln();

    for (int cid = 1; cid <= p; cid++) {
        // Read number of cities n and roads m for country cid
        char buf[100];
        sprintf(buf, "n_%d", cid);
        int n = inf.readInt(1, 50, buf);
        inf.readSpace();
        sprintf(buf, "m_%d", cid);
        int m = inf.readInt(n - 1, 4 * n, buf);
        inf.readEoln();

        // Read hotel costs
        vector<int> h(n + 1);
        for (int i = 1; i <= n; i++) {
            sprintf(buf, "h_%d_%d", cid, i);
            h[i] = inf.readInt(0, 1000000, buf);
            inf.readEoln();
        }

        // Read directed roads
        vector<vector<int>> adj(n + 1);
        for (int ri = 1; ri <= m; ri++) {
            sprintf(buf, "u_%d_%d", cid, ri);
            int u = inf.readInt(1, n, buf);
            inf.readSpace();
            sprintf(buf, "v_%d_%d", cid, ri);
            int v = inf.readInt(1, n, buf);
            ensuref(u != v,
                    "Self-loop detected in country %d at road %d: %d -> %d",
                    cid, ri, u, v);
            inf.readSpace();
            sprintf(buf, "g_%d_%d", cid, ri);
            int g = inf.readInt(0, 1000000, buf);
            inf.readEoln();

            adj[u].push_back(v);
        }

        // Read airport city
        sprintf(buf, "a_%d", cid);
        int a = inf.readInt(1, n, buf);
        inf.readEoln();

        // Validate reachability from city 1 to city a
        vector<char> vis(n + 1, false);
        queue<int> q;
        vis[1] = true;
        q.push(1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        ensuref(vis[a],
                "In country %d, airport city %d is not reachable from home city 1",
                cid, a);
    }

    inf.readEof();
    return 0;
}
