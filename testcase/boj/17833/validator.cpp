#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "N");
    inf.readEoln();

    int r = inf.readInt(1, n, "R");
    inf.readSpace();
    int d = inf.readInt(1, n, "D");
    inf.readEoln();

    int m = inf.readInt(1, 2000, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int h = inf.readInt(2, n, "H_i");
        inf.readSpace();
        inf.readInt(1, 1000000, "T_i");
        inf.readSpace();
        int e1 = inf.readInt(1, h, "E_i1");
        inf.readSpace();
        int e2 = inf.readInt(1, h, "E_i2");
        inf.readEoln();

        ensuref(e1 != e2,
                "model %d has equal entrance floors: %d",
                i,
                e1);
    }

    inf.readEof();
    return 0;
}
