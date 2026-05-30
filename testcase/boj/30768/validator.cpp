#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readSpace();
    int k = inf.readInt(2, 100000, "k");
    inf.readEoln();

    set<pair<int, int>> edge_set;

    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int c = inf.readInt(0, k, "c_i");
        inf.readEoln();

        ensuref(u != v, "Loop detected at edge index %d: (%d, %d)", i + 1, u, v);

        int a = min(u, v), b = max(u, v);
        ensuref(!edge_set.count({a, b}), "Multiple edge detected between %d and %d (edge index %d)", u, v, i + 1);
        edge_set.insert({a, b});
    }

    int a = inf.readInt(1, n, "a");
    inf.readSpace();
    int b = inf.readInt(1, n, "b");
    inf.readEoln();
    ensuref(a != b, "Capitals must be different: a = %d, b = %d", a, b);

    inf.readEof();
}
