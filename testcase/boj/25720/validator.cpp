#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    long long sumN = 0;
    long long sumM = 0;

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 1000000, "m");
        inf.readSpace();
        int p = inf.readInt(1, 1000000000, "p");
        inf.readSpace();
        int x = inf.readInt(0, p - 1, "x");
        inf.readSpace();
        int a = inf.readInt(0, p - 1, "a");
        inf.readSpace();
        int b = inf.readInt(0, p - 1, "b");
        inf.readSpace();
        int c = inf.readInt(0, p - 1, "c");
        inf.readEoln();

        sumN += n;
        sumM += m;
        ensuref(sumN <= 1000000, "sum of n exceeds 1000000 after test case %d", tc);
        ensuref(sumM <= 1000000, "sum of m exceeds 1000000 after test case %d", tc);
    }

    inf.readEof();
    return 0;
}
