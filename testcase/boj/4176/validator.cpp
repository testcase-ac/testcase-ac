#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_DIGITS = 1000000;
    const int MAX_TESTS = 100000;

    int testCount = 0;
    while (true) {
        if (inf.seekEof())
            break;

        string line = inf.readLine("[^]*", "line"); // read whole line, including possible END

        // Disallow empty lines
        ensuref(!line.empty(), "Empty line is not allowed.");

        if (line == "END") {
            // After END, there must be EOF (no extra lines or spaces)
            inf.readEof();
            return 0;
        }

        // Count test cases
        ++testCount;
        ensuref(testCount <= MAX_TESTS,
                "Number of test cases exceeds %d.", MAX_TESTS);

        // Line must contain only digits.
        for (char c : line) {
            ensuref(isdigit(static_cast<unsigned char>(c)),
                    "Line %d contains non-digit character '%c'.", testCount, c);
        }

        // Length constraint: at most one million digits
        int len = (int)line.size();
        ensuref(len >= 1 && len <= MAX_DIGITS,
                "Line %d has invalid digit length %d (must be 1..%d).",
                testCount, len, MAX_DIGITS);

        ensuref(len == 1 || line[0] != '0',
                "Line %d is not a canonical non-negative integer.", testCount);
    }

    // If we exit loop without seeing END, it's invalid
    ensuref(false, "Input must end with a line containing exactly 'END'.");
}
