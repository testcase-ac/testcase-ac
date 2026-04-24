#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and t
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    // Read array a of size n
    inf.readInts(n, 1, 1000000, "a_i");
    inf.readEoln();

    // Read t queries
    for (int i = 0; i < t; i++) {
        int l = inf.readInt(1, n, "l_i");
        inf.readSpace();
        int r = inf.readInt(1, n, "r_i");
        inf.readEoln();
        ensuref(l <= r, "Query %d has l_i > r_i: l_i=%d, r_i=%d", i + 1, l, r);
    }

    inf.readEof();
    return 0;
}
