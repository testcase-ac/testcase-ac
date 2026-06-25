#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000000, "N");
    inf.readSpace();
    int t = inf.readInt(2, 100, "T");
    inf.readSpace();
    int s = inf.readInt(1, 1000, "S");
    inf.readSpace();
    int e = inf.readInt(1, 1000, "E");
    inf.readEoln();

    vector<int> degree(1001, 0);
    set<int> vertices;
    set<pair<int, int>> edges;

    for (int i = 1; i <= t; ++i) {
        int length = inf.readInt(1, 1000, "length_i");
        inf.readSpace();
        int u = inf.readInt(1, 1000, "I1_i");
        inf.readSpace();
        int v = inf.readInt(1, 1000, "I2_i");
        inf.readEoln();

        ensuref(u != v, "trail %d connects intersection %d to itself", i, u);

        pair<int, int> edge = minmax(u, v);
        ensuref(edges.insert(edge).second,
                "duplicate direct trail at index %d between %d and %d", i, u, v);

        ++degree[u];
        ++degree[v];
        vertices.insert(u);
        vertices.insert(v);
    }

    ensuref(vertices.count(s), "starting intersection S=%d is not used by any trail", s);
    ensuref(vertices.count(e), "ending intersection E=%d is not used by any trail", e);

    for (int v : vertices) {
        ensuref(degree[v] >= 2,
                "intersection %d terminates only %d trail(s)", v, degree[v]);
    }

    // CHECK: The statement does not forbid S == E, so equal start and end labels are accepted.
    (void)n;
    inf.readEof();
}
