#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "N");
    inf.readSpace();
    inf.readLong(0LL, 1000000000LL, "A");
    inf.readSpace();
    inf.readInt(1, 5000, "L");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        long long x = inf.readLong(-1LL, 1000000000LL, "X_i");
        inf.readSpace();
        int y = inf.readInt(-1, 5000, "Y_i");
        inf.readEoln();

        ensuref(x != -1 || y != -1, "attack %d has both X_i and Y_i equal to -1", i);
    }

    inf.readEof();
}
