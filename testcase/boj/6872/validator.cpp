#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 999, "a"); // CHECK: divisor counts define the problem over positive integers.
    inf.readEoln();
    int b = inf.readInt(1, 999, "b");
    inf.readEoln();

    // CHECK: the statement describes a range from a lower endpoint to an upper endpoint.
    ensuref(a <= b, "range endpoints must be nondecreasing: a=%d, b=%d", a, b);

    inf.readEof();
}
