#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "n");
    inf.readEoln();

    int previous_t = 0;
    for (int i = 1; i <= n; ++i) {
        int t = inf.readInt(1, 1000000, "t_i");
        inf.readSpace();
        inf.readInt(1, 1000000, "p_i");
        inf.readEoln();

        ensuref(t > previous_t, "t_i must be strictly increasing at index %d", i);
        previous_t = t;
    }

    inf.readInt(0, 1000000, "delta");
    inf.readEoln();
    inf.readEof();
}
