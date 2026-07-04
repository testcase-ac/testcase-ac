#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    int chairmanCount = 0;
    for (int i = 1; i <= n; ++i) {
        int s = inf.readInt(0, i - 1, "s_i");
        inf.readSpace();
        inf.readInt(-100, 100, "a_i");
        inf.readEoln();

        if (s == 0) {
            ++chairmanCount;
        }
    }

    ensuref(chairmanCount == 1, "expected exactly one chairman, found %d", chairmanCount);
    inf.readEof();
}
