#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readSpace();
    int p = inf.readInt(1, 10000, "p");
    inf.readEoln();

    int requiredPositiveGroups = 0;
    int previous = -1;
    bool seenZero = false;

    for (int i = 1; i <= n; ++i) {
        int t = inf.readInt(0, 1000000, "t_i");
        inf.readEoln();

        if (t == 0) {
            seenZero = true;
            previous = t;
            continue;
        }

        ensuref(!seenZero, "positive time score after zero at line %d", i + 1);
        if (requiredPositiveGroups == 0 || previous > t) {
            ++requiredPositiveGroups;
        }
        previous = t;
    }

    ensuref(requiredPositiveGroups <= p,
            "valid scoreboard needs %d positive solved-count groups, but p is %d",
            requiredPositiveGroups, p);

    inf.readEof();
}
