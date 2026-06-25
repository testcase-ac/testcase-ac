#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50, "n");
    inf.readSpace();
    int m = inf.readInt(0, n * (n - 1), "m");
    inf.readSpace();
    inf.readInt(1, 100, "a");
    inf.readSpace();
    inf.readInt(1, 100, "b");
    inf.readSpace();
    inf.readInt(1, 100, "c");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: (%d, %d)", i, u, v);
        ensuref(edges.insert({u, v}).second,
                "duplicate directed edge at edge %d: (%d, %d)", i, u, v);
    }

    inf.readEof();
}
