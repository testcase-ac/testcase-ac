#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 3000, "N");
    inf.readSpace();
    int t = inf.readInt(1, 3000, "T");
    inf.readSpace();
    int s = inf.readInt(0, t, "S");
    inf.readEoln();

    bool hasSchedule = false;
    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 100000, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, 3000, "B_i");
        inf.readEoln();

        if (b <= s || b <= t - s) {
            hasSchedule = true;
        }
    }

    ensuref(hasSchedule, "at least one nonempty schedule must be possible");
    inf.readEof();
}
