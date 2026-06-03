#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "M");
    inf.readSpace();
    int r = inf.readInt(1, n, "R");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u < v, "edge %d must satisfy u < v, found %d %d", i, u, v);
        ensuref(edges.insert({u, v}).second, "duplicate edge %d: %d %d", i, u, v);
    }

    inf.readEof();
}
