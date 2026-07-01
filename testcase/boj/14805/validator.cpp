#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(3, 1000, "N");
        inf.readSpace();
        int r = inf.readInt(0, n, "R");
        inf.readSpace();
        int o = inf.readInt(0, n, "O");
        inf.readSpace();
        int y = inf.readInt(0, n, "Y");
        inf.readSpace();
        int g = inf.readInt(0, n, "G");
        inf.readSpace();
        int b = inf.readInt(0, n, "B");
        inf.readSpace();
        int v = inf.readInt(0, n, "V");
        inf.readEoln();

        ensuref(r + o + y + g + b + v == n,
                "color counts must sum to N, got N=%d and sum=%d",
                n, r + o + y + g + b + v);
        ensuref(o == 0 && g == 0 && v == 0,
                "Small dataset requires O=G=V=0, got O=%d G=%d V=%d",
                o, g, v);
    }

    inf.readEof();
}
