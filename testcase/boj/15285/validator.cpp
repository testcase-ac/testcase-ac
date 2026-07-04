#include "testlib.h"

#include <algorithm>
#include <queue>
#include <set>
#include <vector>

using namespace std;

bool reachesAll(const vector<vector<int>>& graph) {
    int n = static_cast<int>(graph.size()) - 1;
    vector<int> seen(n + 1, 0);
    queue<int> q;

    seen[1] = 1;
    q.push(1);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : graph[v]) {
            if (!seen[to]) {
                seen[to] = 1;
                q.push(to);
            }
        }
    }

    for (int v = 1; v <= n; ++v) {
        if (!seen[v]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not give an upper bound for the number of test
    // cases, so this uses the local practical cap. The aggregate m bound remains
    // the statement's explicit workload limit.
    int testCount = inf.readInt(1, 100000, "testCount");
    inf.readEoln();

    int totalM = 0;

    for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
        setTestCase(caseIndex);

        // CHECK: n has no explicit upper bound. Since m > 2n and sum(m) <=
        // 100000, no valid case can have n above 49999.
        int n = inf.readInt(4, 49999, "n");
        inf.readSpace();
        int m = inf.readInt(2 * n + 1, 100000, "m");
        inf.readEoln();

        totalM += m;
        ensuref(totalM <= 100000, "sum of m exceeds 100000 after case %d", caseIndex);

        set<pair<int, int>> edges;
        vector<vector<int>> graph(n + 1), reverseGraph(n + 1);

        for (int i = 1; i <= m; ++i) {
            int from = inf.readInt(1, n, "x_i");
            inf.readSpace();
            int to = inf.readInt(1, n, "y_i");
            inf.readEoln();

            ensuref(from != to, "case %d edge %d is a loop: %d -> %d", caseIndex, i, from, to);
            ensuref(edges.insert({from, to}).second,
                    "case %d has duplicate directed edge %d -> %d", caseIndex, from, to);

            graph[from].push_back(to);
            reverseGraph[to].push_back(from);
        }

        ensuref(reachesAll(graph), "case %d is not reachable from city 1", caseIndex);
        ensuref(reachesAll(reverseGraph), "case %d cannot reach city 1 from every city", caseIndex);
    }

    inf.readEof();
}
