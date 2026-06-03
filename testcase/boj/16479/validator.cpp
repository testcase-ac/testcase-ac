#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 100, "K");
    inf.readEoln();

    int d1 = inf.readInt(1, 100, "D_1");
    inf.readSpace();
    int d2 = inf.readInt(1, 100, "D_2");
    inf.readEoln();

    ensuref(0 <= d1 - d2 && d1 - d2 < 2 * k,
            "expected 0 <= D_1 - D_2 < 2*K, got K=%d, D_1=%d, D_2=%d",
            k, d1, d2);

    inf.readEof();
}
