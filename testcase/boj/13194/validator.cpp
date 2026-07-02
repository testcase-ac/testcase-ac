#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1250, 1250, "N");
    inf.readSpace();
    int mLim = inf.readInt(500000, 500000, "M_lim");
    inf.readSpace();
    int pLim = inf.readInt(500000, 500000, "P_lim");
    inf.readEoln();

    ensuref(n == 1250, "N must be 1250, got %d", n);
    ensuref(mLim == 500000, "M_lim must be 500000, got %d", mLim);
    ensuref(pLim == 500000, "P_lim must be 500000, got %d", pLim);

    inf.readEof();
}
