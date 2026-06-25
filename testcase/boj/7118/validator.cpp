#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(2, 999999999, "p");
    inf.readSpace();
    // CHECK: The statement says n is natural and describes a number with n ones, so n = 0 is not accepted.
    int n = inf.readInt(1, 999999999, "n");
    inf.readEoln();
    inf.readEof();

    (void)p;
    (void)n;
}
