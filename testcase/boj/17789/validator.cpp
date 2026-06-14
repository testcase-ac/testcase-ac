#include "testlib.h"

#include <cstdlib>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(0, 10000, "p");
    inf.readSpace();
    int v = inf.readInt(0, 10000, "v");
    inf.readEoln();

    for (int i = 0; i < p; ++i) {
        int a = inf.readInt(1, 10000, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, 10000, "b_i");
        inf.readEoln();

        ensuref(std::abs(a - b) <= 1,
                "pedestal %d sides differ by more than one: %d %d",
                i + 1, a, b);
    }

    for (int i = 0; i < v; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(1, 10000, "c_i");
    }
    inf.readEoln();

    inf.readEof();
}
