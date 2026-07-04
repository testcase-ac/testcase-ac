#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(3, 1000, "N");
        inf.readSpace();
        int r = inf.readInt(0, 1000, "R");
        inf.readSpace();
        int o = inf.readInt(0, 1000, "O");
        inf.readSpace();
        int y = inf.readInt(0, 1000, "Y");
        inf.readSpace();
        int g = inf.readInt(0, 1000, "G");
        inf.readSpace();
        int b = inf.readInt(0, 1000, "B");
        inf.readSpace();
        int v = inf.readInt(0, 1000, "V");
        inf.readEoln();

        int sum = r + o + y + g + b + v;
        ensuref(sum == n, "case %d: R+O+Y+G+B+V is %d, expected N=%d", tc, sum, n);
    }

    inf.readEof();
}
