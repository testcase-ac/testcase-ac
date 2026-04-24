#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n, t, m
    int n = inf.readInt(2, 10000, "n");
    inf.readSpace();
    int t = inf.readInt(1, 1000, "t");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    // Read start and end vertices
    int s = inf.readInt(0, n - 1, "s");
    inf.readSpace();
    int e = inf.readInt(0, n - 1, "e");
    inf.readEoln();
    ensuref(s != e, "s and e must be different, but got s=%d, e=%d", s, e);

    // For each time T, read m edges
    for (int T = 1; T <= t; T++) {
        set<pair<int,int>> seen;
        for (int i = 0; i < m; i++) {
            int u = inf.readInt(0, n - 1, "u");
            inf.readSpace();
            int v = inf.readInt(0, n - 1, "v");
            inf.readSpace();
            int w = inf.readInt(1, 10000, "w");
            inf.readEoln();

            ensuref(u != v,
                    "Loop detected at time T=%d, edge index %d: both endpoints = %d",
                    T, i, u);

            int a = min(u, v), b = max(u, v);
            pair<int,int> p = make_pair(a, b);
            ensuref(seen.count(p) == 0,
                    "Multiple edges detected at time T=%d: edge (%d, %d) appears more than once",
                    T, a, b);
            seen.insert(p);
        }
    }

    inf.readEof();
    return 0;
}
