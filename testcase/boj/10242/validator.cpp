#include "testlib.h"

#include <algorithm>
#include <queue>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseIndex = 1;
    while (true) {
        int n = inf.readInt(0, 100, "n");
        inf.readSpace();

        int maxEdges = n * (n - 1) / 2;
        int minEdges = n == 0 ? 0 : n - 1;
        int m = inf.readInt(minEdges, maxEdges, "m");
        inf.readEoln();

        if (n == 0) {
            ensuref(m == 0, "terminating line must be 0 0, found 0 %d", m);
            break;
        }

        setTestCase(caseIndex++);

        vector<int> party = inf.readInts(n, 0, 1, "party");
        (void)party;
        inf.readEoln();

        vector<vector<int>> graph(n + 1);
        vector<int> degree(n + 1, 0);
        set<pair<int, int>> edges;
        for (int i = 1; i <= m; ++i) {
            int a = inf.readInt(1, n, "a");
            inf.readSpace();
            int b = inf.readInt(a + 1, n, "b");
            inf.readEoln();

            ensuref(edges.insert({a, b}).second,
                    "duplicate edge in case %d at index %d: %d %d",
                    caseIndex - 1, i, a, b);
            graph[a].push_back(b);
            graph[b].push_back(a);
            ++degree[a];
            ++degree[b];
        }

        // CHECK: The numeric bounds allow n=1, but the statement also says each
        // governor has at least one friend, so a one-governor test case is not
        // valid.
        for (int v = 1; v <= n; ++v) {
            ensuref(degree[v] > 0,
                    "case %d governor %d has no friends",
                    caseIndex - 1, v);
        }

        vector<bool> seen(n + 1, false);
        queue<int> q;
        seen[1] = true;
        q.push(1);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : graph[v]) {
                if (!seen[to]) {
                    seen[to] = true;
                    q.push(to);
                }
            }
        }

        for (int v = 1; v <= n; ++v) {
            ensuref(seen[v],
                    "case %d graph is disconnected; governor %d is unreachable from governor 1",
                    caseIndex - 1, v);
        }
    }

    inf.readEof();
    return 0;
}
