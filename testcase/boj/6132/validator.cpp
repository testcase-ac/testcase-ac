#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The Korean BOJ statement says 1 <= N, while the embedded English
    // variant says 2 <= N. Follow the primary BOJ statement for this problem.
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    inf.readInt(1, 100, "c");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 100, "h_i");
        inf.readEoln();
    }

    inf.readEof();
}
