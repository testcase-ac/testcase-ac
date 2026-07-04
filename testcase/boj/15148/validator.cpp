#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int h = inf.readInt(0, 100, "h");
    inf.readSpace();
    int a = inf.readInt(0, h, "a");
    inf.readSpace();
    int pMinus = inf.readInt(0, 100, "p_minus");
    inf.readSpace();
    int pZero = inf.readInt(0, 100, "p_zero");
    inf.readSpace();
    int pPlus = inf.readInt(0, 100, "p_plus");
    inf.readEoln();

    ensuref(pMinus + pZero + pPlus == 100,
            "probabilities must sum to 100, found %d",
            pMinus + pZero + pPlus);

    inf.readEof();
}
