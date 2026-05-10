#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // 2. Read permutation p[1..N]
    vector<int> p = inf.readInts(N, 1, N, "p_i");
    inf.readEoln();

    // Check that p is a permutation of 1..N
    vector<bool> seen(N+1, false);
    for (int i = 0; i < N; ++i) {
        ensuref(!seen[p[i]], "p is not a permutation: value %d occurs more than once", p[i]);
        seen[p[i]] = true;
    }
    for (int i = 1; i <= N; ++i) {
        ensuref(seen[i], "p is not a permutation: value %d is missing", i);
    }

    // 3. Read M wormholes, check constraints
    set<pair<int,int>> edges;
    for (int i = 0; i < M; ++i) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "b_i");
        inf.readSpace();
        int w = inf.readInt(1, 1000000000, "w_i");
        inf.readEoln();

        ensuref(a != b, "Wormhole %d: a_i == b_i == %d (no self-loops allowed)", i+1, a);

        int u = min(a, b), v = max(a, b);
        ensuref(!edges.count({u, v}), "Wormhole %d: multiple edges between %d and %d", i+1, u, v);
        edges.insert({u, v});
    }

    inf.readEof();
}
