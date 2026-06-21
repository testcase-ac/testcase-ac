#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int lines = 0;
    int cases = 0;
    while (true) {
        ++lines;
        ensuref(lines <= 1001, "input has more than 1001 lines");

        int n = inf.readInt(0, 5000, "n");
        inf.readSpace();
        int t = inf.readInt(0, 8000, "t");
        inf.readEoln();

        if (n == 0 && t == 0) {
            break;
        }

        setTestCase(++cases);
        ensuref(3500 <= n && n <= 5000, "n must be in [3500, 5000], got %d", n);
        ensuref(1 <= t && t <= 8000, "t must be in [1, 8000], got %d", t);
    }

    // CHECK: The statement gives only an upper bound on input lines, so a
    // sentinel-only file is accepted as the smallest terminated input.
    inf.readEof();
}
