#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readEoln();

    int first = inf.readInt(1, 100, "a_1");
    inf.readEoln();

    bool hasCompleteRound = false;
    bool needsRoundStart = false;
    for (int i = 2; i <= n; ++i) {
        int value = inf.readInt(1, 100, "a_i");
        inf.readEoln();

        if (needsRoundStart) {
            first = value;
            needsRoundStart = false;
            continue;
        }

        if (value % first == 0) {
            hasCompleteRound = true;
            needsRoundStart = true;
        }
    }

    ensuref(hasCompleteRound, "sequence must contain at least one complete round");
    inf.readEof();
}
