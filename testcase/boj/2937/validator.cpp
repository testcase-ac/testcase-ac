#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, n * n, "M");
    inf.readEoln();
    bool canFitRectangle = false;
    for (int rows = 1; rows <= n; ++rows) {
        if (m % rows == 0 && m / rows <= n) {
            canFitRectangle = true;
            break;
        }
    }
    ensuref(canFitRectangle, "M=%d cannot be arranged as a rectangle inside %dx%d board", m, n, n);

    for (int i = 0; i < m; ++i) {
        inf.readInt(1, n, "R_i");
        inf.readSpace();
        inf.readInt(1, n, "C_i");
        inf.readEoln();
    }

    inf.readEof();
}
