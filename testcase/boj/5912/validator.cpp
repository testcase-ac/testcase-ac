#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 25000, "K");
    inf.readEoln();

    ensuref(n % 2 == 1, "N must be odd, got %d", n);

    for (int i = 1; i <= k; ++i) {
        int a = inf.readInt(1, n, "A");
        inf.readSpace();
        int b = inf.readInt(a, n, "B");
        inf.readEoln();
    }

    inf.readEof();
}
