#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The problem does not explicitly give bounds on antenna/eyes.
    // We assume non-negative integers that fit in 32-bit signed range.
    // If the original problem statement (outside this excerpt) had
    // bounds, they should be inserted here instead.
    const int MIN_VAL = 0;
    const int MAX_VAL = 1000000000; // safe generic upper bound

    int antenna = inf.readInt(MIN_VAL, MAX_VAL, "antenna");
    inf.readEoln();
    int eyes = inf.readInt(MIN_VAL, MAX_VAL, "eyes");
    inf.readEoln();

    inf.readEof();
}
