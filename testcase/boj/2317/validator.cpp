#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readLong(1LL, 2147483647LL, "height");
        inf.readEoln();
    }

    inf.readEof();
}
