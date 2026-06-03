#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "M");
    inf.readEoln();

    int previousStart = 0;
    for (int i = 1; i <= m; ++i) {
        int k = inf.readInt(1, n, "k_i");
        inf.readSpace();
        int s = inf.readInt(1, 1000000000, "s_i");
        inf.readSpace();
        int e = inf.readInt(1, 1000000000, "e_i");
        inf.readEoln();

        ensuref(s < e, "reservation %d has s_i >= e_i: %d >= %d", i, s, e);
        ensuref(previousStart < s,
                "start times must be strictly increasing at reservation %d: %d after %d",
                i, s, previousStart);
        previousStart = s;
    }

    inf.readEof();
}
