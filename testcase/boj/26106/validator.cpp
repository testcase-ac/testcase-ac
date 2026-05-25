#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(0, 300000, "m");
    inf.readSpace();
    int n = inf.readInt(1, 30000, "n");
    inf.readSpace();
    int k = inf.readInt(0, 500000, "k");
    inf.readEoln();
    ensuref(m <= 10 * n, "m must be at most 10n, got m=%d n=%d", m, n);

    int source = inf.readInt(0, n - 1, "v");
    inf.readSpace();
    int destination = inf.readInt(0, n - 1, "w");
    inf.readEoln();
    (void)source;
    (void)destination;

    vector<vector<int>> adj(n);
    vector<int> indegree(n), outdegree(n);
    unordered_set<long long> edges;
    edges.reserve((size_t)m * 2 + 1);

    for (int i = 0; i < m; ++i) {
        int x = inf.readInt(0, n - 1, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, n - 1, "y_i");
        inf.readSpace();
        int c = inf.readInt(0, 1000, "c_i");
        inf.readEoln();
        (void)c;

        ensuref(x != y, "self-loop edge at line %d: %d -> %d", i + 1, x, y);

        long long key = 1LL * x * n + y;
        ensuref(edges.insert(key).second, "duplicate edge at line %d: %d -> %d", i + 1, x, y);

        adj[x].push_back(y);
        ++outdegree[x];
        ++indegree[y];
        ensuref(outdegree[x] <= 10, "out-degree of vertex %d exceeds 10", x);
    }

    long long possibleForbiddenTurns = 0;
    for (int y = 0; y < n; ++y) {
        possibleForbiddenTurns += 1LL * indegree[y] * outdegree[y];
    }
    ensuref(k <= possibleForbiddenTurns,
            "k=%d exceeds the number of possible forbidden turns %lld",
            k, possibleForbiddenTurns);

    unordered_set<long long> forbiddenTurns;
    forbiddenTurns.reserve((size_t)k * 2 + 1);
    for (int i = 0; i < k; ++i) {
        int x = inf.readInt(0, n - 1, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, n - 1, "y_i");
        inf.readSpace();
        int z = inf.readInt(0, n - 1, "z_i");
        inf.readEoln();

        ensuref(edges.count(1LL * x * n + y) != 0,
                "forbidden turn %d uses missing edge %d -> %d", i + 1, x, y);
        ensuref(edges.count(1LL * y * n + z) != 0,
                "forbidden turn %d uses missing edge %d -> %d", i + 1, y, z);

        long long key = (1LL * x * n + y) * n + z;
        ensuref(forbiddenTurns.insert(key).second,
                "duplicate forbidden turn at line %d: %d %d %d", i + 1, x, y, z);
    }

    inf.readEof();
}
