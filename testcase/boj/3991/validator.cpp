#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(1, 10, "h");
    inf.readSpace();
    int w = inf.readInt(1, 10, "w");
    inf.readSpace();
    int c = inf.readInt(1, 9, "c");
    inf.readEoln();

    int total = 0;
    for (int i = 0; i < c; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int count = inf.readInt(1, h * w, "count_i");
        total += count;
    }
    inf.readEoln();

    ensuref(total == h * w, "sum of color counts is %d, expected %d", total, h * w);
    inf.readEof();
}
