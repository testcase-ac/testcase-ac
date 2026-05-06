#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The input is a sequence of integers, one per line.
    // All integers, except the last one, are positive.
    // The last integer must be exactly 0 and is a terminator.
    // Each integer is on its own line, no extra spaces.

    bool seenZero = false;
    int maxCases = 100000;
    int caseCount = 0;

    while (true) {
        // Read an integer per line; canonical form and full 32-bit range.
        int n = inf.readInt(-2147483648, 2147483647, "n");
        inf.readEoln();

        if (n == 0) {
            // Terminator: must be the last line.
            seenZero = true;
            break;
        }

        // All other integers must be positive.
        ensuref(n > 0, "All integers except the last must be positive, found %d", n);

        ++caseCount;
        ensuref(caseCount <= maxCases,
                "Number of test cases (positive integers before 0) exceeds limit %d", maxCases);
    }

    ensuref(seenZero, "Input must terminate with a single '0' line");

    inf.readEof();
}
