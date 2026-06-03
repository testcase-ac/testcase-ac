#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = inf.readInt(2, 20000, "W");
    inf.readEoln();
    inf.readEof();

    ensuref(w % 2 == 0, "W must be even: %d", w);

    int half = w / 2;
    int k = 1;
    while (k * k < half) {
        ++k;
    }
    ensuref(k * k == half, "no even square side produces W: %d", w);
}
