#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readEoln();

    string s = inf.readToken("[()]{2,100000}", "S");
    ensuref((int)s.size() == n, "S length must be N: length=%d, N=%d", (int)s.size(), n);
    inf.readEoln();

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        int l = inf.readInt(1, n, "L_i");
        inf.readSpace();
        int r = inf.readInt(1, n, "R_i");
        ensuref(l <= r, "L_i must not exceed R_i at query %d: L=%d, R=%d", i, l, r);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
