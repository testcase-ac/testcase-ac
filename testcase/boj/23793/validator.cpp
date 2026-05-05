#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 200000, "M");
    inf.readEoln();

    // 2. Read M edges, check constraints
    set<pair<int, int>> edge_set;
    for (int i = 0; i < M; ++i) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readSpace();
        int w = inf.readInt(1, 10000, "w");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected at edge %d: u == v == %d", i+1, u);
        ensuref(!edge_set.count({u, v}), "Multiple edges detected between (%d, %d) at edge %d", u, v, i+1);
        edge_set.insert({u, v});
    }

    // 3. Read X, Y, Z
    int X = inf.readInt(1, N, "X");
    inf.readSpace();
    int Y = inf.readInt(1, N, "Y");
    inf.readSpace();
    int Z = inf.readInt(1, N, "Z");
    inf.readEoln();

    ensuref(X != Y, "X == Y == %d, but X and Y must be different", X);
    ensuref(X != Z, "X == Z == %d, but X and Z must be different", X);
    ensuref(Y != Z, "Y == Z == %d, but Y and Z must be different", Y);

    inf.readEof();
}
