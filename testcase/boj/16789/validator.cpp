#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readLong(1LL, 1000000000LL, "A_i");
    }
    inf.readEoln();

    for (int j = 0; j < m; ++j) {
        int l = inf.readInt(1, n, "L_j");
        inf.readSpace();
        int r = inf.readInt(l, n, "R_j");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
