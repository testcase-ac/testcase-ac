#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    for (int edge = 1; edge <= m; ++edge) {
        int i = inf.readInt(1, n, "initial_i");
        inf.readSpace();
        int j = inf.readInt(1, n, "initial_j");
        inf.readEoln();

        ensuref(i != j, "initial road %d must connect two distinct cities: %d %d", edge, i, j);
    }

    int q = inf.readInt(1, 500, "q");
    inf.readEoln();

    for (int plan = 1; plan <= q; ++plan) {
        int i = inf.readInt(1, n, "plan_i");
        inf.readSpace();
        int j = inf.readInt(1, n, "plan_j");
        inf.readEoln();

        ensuref(i != j, "planned road %d must connect two distinct cities: %d %d", plan, i, j);
    }

    inf.readEof();
}
