#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 300000, "M");
    inf.readSpace();
    int s = inf.readInt(1, n, "S");
    inf.readSpace();
    int t = inf.readInt(1, n, "T");
    inf.readEoln();

    ensuref(s != t, "S and T must be distinct: S=%d, T=%d", s, t);

    set<pair<int, int>> edges;
    set<int> colors;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int c = inf.readInt(1, 1000000000, "c_i");
        inf.readEoln();

        ensuref(u != v, "loop at edge %d: (%d, %d)", i, u, v);
        ensuref(edges.insert({u, v}).second,
                "multiple directed edge at edge %d: (%d, %d)", i, u, v);
        ensuref(colors.insert(c).second, "duplicate color at edge %d: %d", i, c);
    }

    inf.readEof();
}
