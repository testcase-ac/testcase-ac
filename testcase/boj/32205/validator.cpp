#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(1, 1000000, "a");
        inf.readSpace();
        int b = inf.readInt(1, 1000000, "b");
        inf.readSpace();
        int c = inf.readInt(1, 1000000, "c");
        inf.readEoln();

        ensuref(a < b && b < c,
                "triangle %d must have strictly increasing side lengths: %d %d %d",
                i, a, b, c);
        ensuref(a + b > c,
                "triangle %d must exist, but %d + %d <= %d",
                i, a, b, c);
    }

    inf.readEof();
}
