#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M, Q
    int N = inf.readInt(2, 500, "N");
    inf.readSpace();
    int M = inf.readInt(0, 10000, "M");
    inf.readSpace();
    int Q = inf.readInt(0, 40000, "Q");
    inf.readEoln();

    // 2. Read N integers: annoyance times
    vector<int> annoy(N+1);
    for (int i = 1; i <= N; ++i) {
        annoy[i] = inf.readInt(1, 10000, "annoy_i");
        if (i < N) inf.readSpace();
        else inf.readEoln();
    }

    // 3. Read M roads: a, b, d
    set<pair<int,int>> edges;
    for (int i = 0; i < M; ++i) {
        int a = inf.readInt(1, N, "a");
        inf.readSpace();
        int b = inf.readInt(1, N, "b");
        inf.readSpace();
        int d = inf.readInt(1, 10000, "d");
        inf.readEoln();

        ensuref(a != b, "Self-loop detected at edge %d: (%d, %d)", i+1, a, b);
        int u = min(a, b), v = max(a, b);
        ensuref(!edges.count({u, v}), "Multiple edge detected between %d and %d (edge %d)", a, b, i+1);
        edges.insert({u, v});
    }

    // 4. Read Q queries: S, T
    for (int i = 0; i < Q; ++i) {
        int S = inf.readInt(1, N, "S");
        inf.readSpace();
        int T = inf.readInt(1, N, "T");
        inf.readEoln();
    }

    inf.readEof();
}
