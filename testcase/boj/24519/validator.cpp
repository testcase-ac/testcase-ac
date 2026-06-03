#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 18, "N");
    inf.readSpace();
    int m = inf.readInt(0, n * (n - 1), "M");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int c = inf.readInt(1, 5000000, "c_i");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge index %d: %d -> %d", i + 1, u, v);
        ensuref(edges.insert({u, v}).second,
                "duplicate directed edge at index %d: %d -> %d", i + 1, u, v);
    }

    inf.readEof();
}
