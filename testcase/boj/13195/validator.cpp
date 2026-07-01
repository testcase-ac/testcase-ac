#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5101, 5101, "N");
    inf.readSpace();
    int mLim = inf.readInt(500000, 500000, "M_lim");
    inf.readSpace();
    int pLim = inf.readInt(500000, 500000, "P_lim");
    inf.readEoln();
    inf.readEof();

    ensuref(n == 5101, "N must be exactly 5101");
    ensuref(mLim == 500000, "M_lim must be exactly 500000");
    ensuref(pLim == 500000, "P_lim must be exactly 500000");
}
