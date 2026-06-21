#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readLong(1LL, 1000000000LL, "k");
        inf.readEoln();
    }

    inf.readEof();
}
