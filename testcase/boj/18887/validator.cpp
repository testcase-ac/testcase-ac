#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int sa = inf.readInt(1, 1000000000, "sa");
        inf.readSpace();
        int ea = inf.readInt(1, 1000000000, "ea");
        inf.readSpace();
        int sb = inf.readInt(1, 1000000000, "sb");
        inf.readSpace();
        int eb = inf.readInt(1, 1000000000, "eb");
        inf.readEoln();

        ensuref(sa <= ea, "lecture %d has sa > ea: %d > %d", i, sa, ea);
        ensuref(sb <= eb, "lecture %d has sb > eb: %d > %d", i, sb, eb);
    }

    inf.readEof();
}
