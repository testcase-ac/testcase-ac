#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    int sumN = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 2000, "n");
        inf.readSpace();
        int maxA = (n - 1) * (n - 1) + 1;
        inf.readInt(1, maxA, "a");
        inf.readEoln();

        sumN += n;
        ensuref(sumN <= 2000, "sum of n exceeds 2000 at case %d", tc);
    }

    inf.readEof();
    return 0;
}
