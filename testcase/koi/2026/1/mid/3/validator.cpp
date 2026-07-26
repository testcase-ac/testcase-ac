#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int n = inf.readInt(2, 300000, "n");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000000000000LL, "a");
    inf.readEoln();

    for (int j = 1; j < n; ++j) {
        inf.readInt(j + 1, n, "c");
        if (j + 1 < n) {
            inf.readSpace();
        }
    }
    inf.readEoln();

    inf.readLongs(n - 1, 1LL, 1000000000000LL, "l");
    inf.readEoln();
    inf.readEof();
}
