#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int datasetCount = 0;
    while (true) {
        int n = inf.readInt(0, 1000, "N");
        inf.readSpace();
        int m = inf.readInt(0, 1000, "M");
        inf.readEoln();

        if (n == 0 && m == 0) {
            break;
        }

        ++datasetCount;
        setTestCase(datasetCount);
        ensuref(datasetCount <= 50, "number of datasets exceeds 50");
        ensuref(2 <= n, "N must be at least 2, got %d", n);
        ensuref(1 <= m, "M must be at least 1, got %d", m);

        vector<vector<int>> graph(n + 1);
        set<pair<int, int>> edges;
        for (int i = 1; i <= m; ++i) {
            int u = inf.readInt(1, n, "u_i");
            inf.readSpace();
            int v = inf.readInt(1, n, "v_i");
            inf.readEoln();

            ensuref(u < v, "edge %d must satisfy u_i < v_i, got %d %d", i, u, v);
            ensuref(edges.insert({u, v}).second,
                    "duplicate edge at index %d: %d %d", i, u, v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        vector<int> stack = {1};
        vector<bool> seen(n + 1, false);
        seen[1] = true;
        for (size_t i = 0; i < stack.size(); ++i) {
            int u = stack[i];
            for (int v : graph[u]) {
                if (!seen[v]) {
                    seen[v] = true;
                    stack.push_back(v);
                }
            }
        }

        for (int i = 1; i <= n; ++i) {
            ensuref(seen[i], "graph is not connected; vertex %d is unreachable", i);
        }
    }

    // CHECK: The statement gives only an upper bound on dataset count, so reject
    // a terminator-only file as an empty instance.
    ensuref(datasetCount >= 1, "at least one dataset is required");
    inf.readEof();
}
