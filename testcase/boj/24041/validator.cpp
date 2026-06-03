#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    long long g = inf.readLong(1LL, 1000000000LL, "G");
    inf.readSpace();
    int k = inf.readInt(0, n - 1, "K");
    inf.readEoln();

    long long sumS = 0;
    for (int i = 1; i <= n; ++i) {
        long long s = inf.readLong(1LL, 1000000000LL, "S_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "L_i");
        inf.readSpace();
        inf.readInt(0, 1, "O_i");
        inf.readEoln();

        sumS += s;
        ensuref(sumS <= g, "sum of S_i exceeds G after ingredient %d", i);
    }

    inf.readEof();
}
