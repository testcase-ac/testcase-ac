#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement only gives N <= 50000, but describes a non-empty
    // collection of diamonds and asks for a positive output.
    int n = inf.readInt(1, 50000, "N");
    inf.readSpace();
    inf.readLong(0LL, 1000000000LL, "K");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readLong(1LL, 1000000000LL, "size_i");
        inf.readEoln();
    }

    inf.readEof();
}
