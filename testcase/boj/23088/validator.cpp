#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "n");
    inf.readEoln();

    int previous_t = 0;
    for (int i = 1; i <= n; ++i) {
        int t = inf.readInt(0, 300000, "t_i");
        inf.readSpace();
        int p = inf.readInt(0, 1000, "p_i");
        inf.readSpace();
        int b = inf.readInt(0, 1000, "b_i");
        inf.readEoln();

        ensuref(i == 1 || previous_t <= t,
                "t_i must be nondecreasing: t_%d=%d, t_%d=%d",
                i - 1,
                previous_t,
                i,
                t);
        previous_t = t;
        (void)p;
        (void)b;
    }

    inf.readEof();
}
