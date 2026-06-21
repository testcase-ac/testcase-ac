#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "N");
    inf.readSpace();
    int l = inf.readInt(1, 100000000, "L");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        int d = inf.readInt(1, l, format("D_%d", i + 1));
        inf.readSpace();
        int c = inf.readInt(1, 1000, format("C_%d", i + 1));

        int previous = -1;
        for (int j = 0; j < c; ++j) {
            inf.readSpace();
            int start = inf.readInt(0, l, format("S_%d_%d", i + 1, j + 1));
            ensuref(start > previous,
                    "showtimes for movie %d must be distinct and increasing", i + 1);
            previous = start;
        }
        inf.readEoln();
    }

    inf.readEof();
}
