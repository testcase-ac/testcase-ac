#include "testlib.h"

#include <queue>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxN = 1000;
    const int maxE = maxN * maxN + 1;

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, maxN, "N");
        inf.readSpace();
        // CHECK: E has no written upper bound; cap it near the N^2 graph scale.
        int e = inf.readInt(1, maxE, "E");
        inf.readSpace();
        int a = inf.readInt(0, n - 1, "A");
        inf.readSpace();
        int b = inf.readInt(0, n - 1, "B");
        inf.readEoln();

        ensuref(a != b, "A and B must differ in test case %d", tc);

        vector<vector<int>> graph(n);
        for (int i = 0; i < e; ++i) {
            int u = inf.readInt(0, n - 1, "U");
            inf.readSpace();
            int v = inf.readInt(0, n - 1, "V");
            inf.readSpace();
            int w = inf.readInt(1, 1000, "W");
            inf.readEoln();

            ensuref(u != v, "self-loop at edge %d in test case %d", i + 1, tc);
            graph[u].push_back(v);
            (void)w;
        }

        // CHECK: the requested ratio is undefined when no path exists.
        vector<char> seen(n, false);
        queue<int> q;
        seen[a] = true;
        q.push(a);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : graph[u]) {
                if (!seen[v]) {
                    seen[v] = true;
                    q.push(v);
                }
            }
        }
        ensuref(seen[b], "B must be reachable from A in test case %d", tc);
    }

    inf.readEof();
}
