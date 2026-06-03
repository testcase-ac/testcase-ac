#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 500000, "M");
    inf.readSpace();
    int a = inf.readInt(1, n, "A");
    inf.readSpace();
    int b = inf.readInt(1, n, "B");
    inf.readSpace();
    int c = inf.readInt(1, 2000000, "C");
    inf.readEoln();

    ensuref(a != b, "A and B must be distinct: %d", a);

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int w = inf.readInt(1, 20, "w_i");
        inf.readEoln();

        ensuref(u != v, "edge %d has equal endpoints: %d", i, u);
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second, "duplicate edge %d: (%d, %d)", i, u, v);
    }

    inf.readEof();
}
