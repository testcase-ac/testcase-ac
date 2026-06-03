#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(10, 100, "X");
        inf.readSpace();
        int y = inf.readInt(1, 100, "Y");
        inf.readSpace();
        int smallSize = inf.readInt(1, 99, "S_M");
        inf.readSpace();
        int smallPrice = inf.readInt(10, 99, "P_M");
        inf.readSpace();
        int largeSize = inf.readInt(2, 100, "S_V");
        inf.readSpace();
        int largePrice = inf.readInt(11, 100, "P_V");
        inf.readEoln();

        ensuref(smallSize < largeSize,
                "ingredient %d violates S_M < S_V: %d >= %d",
                i, smallSize, largeSize);
        ensuref(smallPrice < largePrice,
                "ingredient %d violates P_M < P_V: %d >= %d",
                i, smallPrice, largePrice);
        (void)x;
        (void)y;
        (void)m;
    }

    inf.readEof();
}
