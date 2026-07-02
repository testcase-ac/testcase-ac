#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement says there are n people but only gives an upper bound.
    // A bridge-crossing instance without people is vacuous, so require at least one.
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        // CHECK: Crossing times are bounded above by 100; positive integer seconds
        // are required because zero-time crossing is not a meaningful speed here.
        inf.readInt(1, 100, "time");
        inf.readEoln();
    }

    inf.readEof();
}
