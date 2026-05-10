#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: n, m, s, e
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 300, "m");
    inf.readSpace();
    int s = inf.readInt(1, n, "s");
    inf.readSpace();
    int e = inf.readInt(1, n, "e");
    ensuref(s != e, "Start city s (%d) must be different from end city e (%d)", s, e);
    inf.readEoln();

    // Read m undirected roads
    for (int i = 0; i < m; i++) {
        int p = inf.readInt(1, n, "p_i");
        inf.readSpace();
        int r = inf.readInt(1, n, "r_i");
        ensuref(p != r, "Loop detected on edge %d: endpoints are equal (%d)", i+1, p);
        inf.readSpace();
        int c = inf.readInt(0, 100, "c_i");
        inf.readSpace();
        int t = inf.readInt(0, 100, "t_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
