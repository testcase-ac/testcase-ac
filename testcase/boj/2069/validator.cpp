#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int left = inf.readInt(1, 32767, "left");
        inf.readSpace();
        int right = inf.readInt(1, 32767, "right");
        inf.readEoln();

        ensuref(left < right,
                "mountain %d endpoints must be sorted and distinct: %d %d",
                i, left, right);
    }

    inf.readEof();
}
