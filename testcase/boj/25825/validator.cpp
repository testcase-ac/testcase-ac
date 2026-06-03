#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int time[12][12];
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (i == j) {
                time[i][j] = inf.readInt(0, 0, "time");
            } else {
                time[i][j] = inf.readInt(1, 1000, "time");
            }

            if (j + 1 == 12) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    for (int i = 0; i < 12; ++i) {
        for (int j = i + 1; j < 12; ++j) {
            ensuref(time[i][j] == time[j][i],
                    "time matrix must be symmetric at (%d, %d): %d != %d",
                    i + 1, j + 1, time[i][j], time[j][i]);
        }
    }

    inf.readEof();
}
