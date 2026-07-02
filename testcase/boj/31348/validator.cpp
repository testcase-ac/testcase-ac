#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    int previous = 0;
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }

        int current = inf.readInt(1, 1000000, "a_i");
        ensuref(current > previous,
                "a_i must be strictly increasing at index %d: %d <= %d",
                i, current, previous);
        previous = current;
    }
    inf.readEoln();

    inf.readEof();
}
