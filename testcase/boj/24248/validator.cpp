#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 150000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        int s = inf.readInt(0, 1000000, "s");
        inf.readSpace();
        int e = inf.readInt(1, 1000000, "e");
        inf.readSpace();
        inf.readInt(0, 1000000, "a");
        inf.readEoln();

        ensuref(s < e, "start time must be less than end time at musician %d: s=%d e=%d", i + 1, s, e);
    }

    inf.readEof();
}
