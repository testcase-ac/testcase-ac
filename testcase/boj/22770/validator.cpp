#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    for (int tc = 1; tc <= n; ++tc) {
        int a1 = inf.readInt(1, 100, "a1");
        inf.readSpace();
        int b1 = inf.readInt(1, 100, "b1");
        inf.readEoln();
        ensuref(a1 >= b1, "case %d: orbit A foci are not on the x-axis", tc);

        int a2 = inf.readInt(1, 100, "a2");
        inf.readSpace();
        int b2 = inf.readInt(1, 100, "b2");
        inf.readEoln();
        ensuref(b2 >= a2, "case %d: orbit B foci are not on the y-axis", tc);
    }

    inf.readEof();
}
