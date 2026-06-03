#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 500000, "N");
    inf.readEoln();

    for (int i = 1; i <= n - 2; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(1, n, format("a_%d", i));
    }
    inf.readEoln();

    inf.readEof();
}
