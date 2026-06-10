#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int count = 0;
    while (!inf.seekEof()) {
        ++count;
        ensuref(count <= 100, "input contains more than 100 integers");
        inf.readInt(1, 999999, "x_i");
    }

    // CHECK: The statement does not give a lower bound, but the requested
    // maximum GCD among pairs is undefined with fewer than two integers.
    ensuref(count >= 2, "input must contain at least two integers");
    inf.readEof();
}
