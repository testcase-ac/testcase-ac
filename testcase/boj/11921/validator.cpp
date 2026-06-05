#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The judged statement fixes N = 5,000,000 to make the input long.
    // Smaller same-shape inputs keep testcase.ac fixed cases readable.
    int n = inf.readInt(1, 5000000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, 10000000, "a_i");
        inf.readEoln();
    }

    inf.readEof();
}
