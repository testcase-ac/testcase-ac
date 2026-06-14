#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 150, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        long long start = inf.readLong(0LL, 1000000000LL, "start");
        inf.readSpace();
        long long end = inf.readLong(0LL, 1000000000LL, "end");
        inf.readEoln();

        // CHECK: The statement names start and end times of a program but does not
        // spell out ordering; a valid program interval must have positive length.
        ensuref(start < end, "program %d has start >= end: %lld >= %lld", i, start, end);
    }

    inf.readEof();
}
