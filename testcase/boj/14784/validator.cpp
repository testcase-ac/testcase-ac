#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int start = inf.readInt(1, 1000000, "start");
    inf.readSpace();
    int end = inf.readInt(1, 1000000, "end");
    inf.readEoln();

    ensuref(start <= end, "start must not exceed end: start=%d end=%d", start, end);

    inf.readEof();
}
