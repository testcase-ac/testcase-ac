#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: D is not explicitly bounded; D > 5 cannot fit two D-digit primes
    // into any integer no greater than 2,000,000,000.
    inf.readInt(1, 5, "D");
    inf.readSpace();
    inf.readInt(1, 2000000000, "N");
    inf.readEoln();
    inf.readEof();
}
