#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 300000, "m");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(edges.insert({u, v}).second,
                "duplicate directed edge at index %d: (%d, %d)", i + 1, u, v);
    }

    int t = inf.readInt(1, n, "t");
    inf.readEoln();

    set<int> tests;
    for (int i = 0; i < t; ++i) {
        int ti = inf.readInt(1, n, "t_i");
        inf.readEoln();

        ensuref(tests.insert(ti).second,
                "duplicate test function at index %d: %d", i + 1, ti);
    }

    inf.readEof();
}
