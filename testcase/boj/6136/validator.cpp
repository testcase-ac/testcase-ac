#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readSpace();
    int r = inf.readInt(1, n, "R");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int start = inf.readInt(0, n - 1, "starting_hour_i");
        inf.readSpace();
        int end = inf.readInt(start + 1, n, "ending_hour_i");
        inf.readSpace();
        inf.readInt(1, 1000000, "efficiency_i");
        inf.readEoln();
    }

    inf.readEof();
}
