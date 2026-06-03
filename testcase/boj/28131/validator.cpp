#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 10000, "n");
    inf.readSpace();
    int max_m = min(100000, n * (n - 1));
    int m = inf.readInt(1, max_m, "m");
    inf.readSpace();
    int k = inf.readInt(1, 50, "k");
    inf.readEoln();

    int s = inf.readInt(1, n, "s");
    inf.readSpace();
    int t = inf.readInt(1, n, "t");
    inf.readEoln();
    ensuref(s != t, "s and t must be different: %d", s);

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int w = inf.readInt(1, 1000, "w_i");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge index %d: (%d, %d)", i, u, v);
        (void)w;
    }

    inf.readEof();
}
