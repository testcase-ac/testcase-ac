#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int kMinValue = -6000000;
    const int kMaxValue = 6000000;
    // CHECK: The statement does not cap the number of data lines, so use the
    // repo default practical cap for an unbounded repeated-input format.
    const int kMaxCases = 100000;

    int cases = 0;
    while (true) {
        int a = inf.readInt(kMinValue, kMaxValue, "a");
        inf.readSpace();
        int d = inf.readInt(kMinValue, kMaxValue, "d");
        inf.readSpace();
        int v = inf.readInt(kMinValue, kMaxValue, "v");
        inf.readEoln();

        if (a == 0 && d == 0 && v == 0) {
            break;
        }

        ++cases;
        ensuref(cases <= kMaxCases, "too many data lines: %d", cases);
        ensuref(d != 0, "difference must be non-zero on data line %d", cases);
    }

    inf.readEof();
}
