#include "testlib.h"
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 200000, "M");
    inf.readEoln();

    // Check edges for loops and duplicates
    set<pair<int,int>> edges;
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readSpace();
        long long a = inf.readLong(-1000000000LL, 1000000000LL, "a_i");
        inf.readSpace();
        long long b = inf.readLong(-1000000000LL, 1000000000LL, "b_i");
        inf.readEoln();

        ensuref(u != v,
                "Loop detected at edge index %d: (%d,%d)", i, u, v);

        int x = min(u, v), y = max(u, v);
        pair<int,int> e = make_pair(x, y);
        ensuref(!edges.count(e),
                "Multiple edges detected connecting nodes %d and %d", x, y);
        edges.insert(e);
    }

    // Read T
    long long T = inf.readLong(-2000000000000000LL, 2000000000000000LL, "T");
    inf.readEoln();

    inf.readEof();
    return 0;
}
