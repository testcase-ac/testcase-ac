#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 5000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 5000, "M");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        long long l = inf.readLong(1LL, 1000000000LL, "l");
        inf.readSpace();
        long long r = inf.readLong(l, 1000000000LL, "r");
        inf.readEoln();

        ensuref(u != v, "river %d is a self-loop at village %d", i, u);
        pair<int, int> edge = minmax(u, v);
        ensuref(edges.insert(edge).second, "duplicate river %d between villages %d and %d", i, u, v);
    }

    int k = inf.readInt(1, 500000, "K");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readLong(1LL, 1000000000LL, "size");
    }
    inf.readEoln();

    inf.readEof();
}
