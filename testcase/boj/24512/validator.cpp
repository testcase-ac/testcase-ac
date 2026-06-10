#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 9, "N");
    inf.readSpace();
    int m = inf.readInt(0, n * (n - 1), "M");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        int c = inf.readInt(1, 5000000, "c");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: %d -> %d", i, u, v);
        ensuref(edges.insert({u, v}).second,
                "duplicate directed edge at edge %d: %d -> %d with cost %d",
                i, u, v, c);
    }

    inf.readEof();
}
