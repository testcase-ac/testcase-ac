#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_POINTS = 100000; // default upper bound on number of lines
    int cnt = 0;

    while (true) {
        // Each line: two real numbers (as tokens) separated by a single space.
        // The problem statement does not restrict the exact textual format of the reals,
        // so we must NOT enforce canonical numeric formatting here.
        //
        // We only need to ensure they are tokens without spaces and that the
        // terminating line is exactly "0 0".
        string sx = inf.readToken("[^ ]+", "x");
        inf.readSpace();
        string sy = inf.readToken("[^ ]+", "y");
        inf.readEoln();

        // Check number-of-lines bound before processing termination.
        ensuref(cnt <= MAX_POINTS, "Too many points, more than %d lines before terminating '0 0'", MAX_POINTS);

        // Termination condition is textual: line must be exactly "0 0".
        if (sx == "0" && sy == "0") {
            break;
        }

        // No other constraints are specified on the real numbers:
        // they can be any tokens (including things like "-0.12", ".5", "1e3", etc.).
        ++cnt;
    }

    inf.readEof();
}
