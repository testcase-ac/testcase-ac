#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "k");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(0LL, 1000000000LL, "a_i");
        inf.readSpace();
        inf.readLong(0LL, 1000000000LL, "b_i");
        inf.readEoln();
        // CHECK: The statement bounds a_i and b_i independently and does not state a_i <= b_i.
    }

    inf.readEof();
}
