#include "testlib.h"
#include <set>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // Read coordinates
    for (int i = 1; i <= N; i++) {
        char buf[32];
        sprintf(buf, "x_%d", i);
        int x = inf.readInt(0, 1000000, buf);
        inf.readSpace();
        sprintf(buf, "y_%d", i);
        int y = inf.readInt(0, 1000000, buf);
        inf.readEoln();
    }

    // No more edges than possible in a simple undirected graph
    long long maxEdges = (long long)N * (N - 1) / 2;
    ensuref(M <= maxEdges, "Too many edges: M=%d, but at most %lld for N=%d", M, maxEdges, N);

    // Read existing edges, check for loops and duplicates
    set<pair<int,int>> seen;
    for (int i = 1; i <= M; i++) {
        char buf[32];
        sprintf(buf, "u_%d", i);
        int u = inf.readInt(1, N, buf);
        inf.readSpace();
        sprintf(buf, "v_%d", i);
        int v = inf.readInt(1, N, buf);
        inf.readEoln();

        ensuref(u != v, "Loop detected at edge %d: (%d,%d)", i, u, v);
        int a = min(u, v), b = max(u, v);
        ensuref(!seen.count({a,b}),
                "Multiple edges detected at edge %d: (%d,%d)", i, a, b);
        seen.insert({a,b});
    }

    // File ends immediately after last newline
    inf.readEof();
    return 0;
}
