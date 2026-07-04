#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int t = inf.readInt(1, 100, "t");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int prev = -1;
        for (int j = 0; j <= t; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            int score = inf.readInt(0, 10000, "s_i_j");
            ensuref(prev <= score,
                    "scores for subject %d are not nondecreasing at hour %d: %d > %d",
                    i, j, prev, score);
            prev = score;
        }
        inf.readEoln();
    }

    int prev = -1;
    for (int x = 0; x <= t; ++x) {
        if (x > 0) {
            inf.readSpace();
        }
        int fatigue = inf.readInt(0, 10000, "d_x");
        ensuref(prev <= fatigue,
                "fatigue values are not nondecreasing at hour %d: %d > %d",
                x, prev, fatigue);
        prev = fatigue;
    }
    inf.readEoln();

    inf.readEof();
}
