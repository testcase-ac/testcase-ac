#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    while (true) {
        // Read n and m
        int n = inf.readInt(0, 500, "n");
        inf.readSpace();
        // m max when n=500 is 500*499/2 = 124750
        int m = inf.readInt(0, 124750, "m");
        inf.readEoln();

        // Termination condition
        if (n == 0 && m == 0) {
            break;
        }

        // Now this is a real test case
        tc++;
        ensuref(tc <= 100000, "Number of test cases exceeds 100000: %d", tc);
        ensuref(n >= 1, "n must be at least 1 for a test case, but got %d", n);
        int maxEdges = n * (n - 1) / 2;
        ensuref(m <= maxEdges,
                "m must be <= n*(n-1)/2 = %d for n = %d, but got m = %d",
                maxEdges, n, m);

        // Read edges, ensure valid simple undirected graph
        set<pair<int,int>> edges;
        for (int i = 0; i < m; i++) {
            int u = inf.readInt(1, n, "u");
            inf.readSpace();
            int v = inf.readInt(1, n, "v");
            inf.readEoln();

            // No loops
            ensuref(u != v,
                    "Loop detected at edge index %d: (%d, %d)", i, u, v);
            // No multiple edges (undirected)
            int a = min(u, v), b = max(u, v);
            pair<int,int> p = make_pair(a, b);
            ensuref(!edges.count(p),
                    "Multiple edges detected at edge index %d: (%d, %d)", i, u, v);
            edges.insert(p);
        }
    }

    inf.readEof();
    return 0;
}
