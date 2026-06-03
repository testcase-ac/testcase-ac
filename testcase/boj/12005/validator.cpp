#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives only N <= 1000, but the collection and output
    // are non-vacuous, so require at least one diamond.
    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int k = inf.readInt(0, 10000, "k");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, 10000, "diamond_size");
        inf.readEoln();
    }

    inf.readEof();
}
