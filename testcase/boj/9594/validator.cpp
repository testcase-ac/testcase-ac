#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_N = 1000000000000000000LL;
    const int MAX_LINES = 1000;

    for (int line = 1; line <= MAX_LINES; ++line) {
        long long n = inf.readLong(-1LL, MAX_N, "n");
        inf.readEoln();

        if (n == -1) {
            inf.readEof();
            return 0;
        }

        ensuref(n >= 0, "n must be in [0, 10^18] or the terminator -1");
    }

    ensuref(false, "input must contain a -1 terminator within at most 1000 lines");
}
