#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    int line_no = 0;
    // Read lines until we encounter the terminating "0"
    while (true) {
        // Read a line of digits
        string s = inf.readLine("[0-9]+", "N");
        line_no++;

        // Check length constraint: up to 1000 digits
        ensuref((int)s.size() <= 1000,
                "Length of N at line %d is %d, exceeds limit 1000",
                line_no, (int)s.size());

        // No leading zeros allowed except for the single character "0"
        if (s.size() > 1) {
            ensuref(s[0] != '0',
                    "Leading zero in N at line %d: \"%s\"",
                    line_no, s.c_str());
        }

        // If this line is "0", it must be the terminating line
        if (s == "0") {
            break;
        }

        // It's a positive integer test case
        cases++;
        ensuref(cases <= 100000,
                "Number of test cases (%d) exceeds limit 100000",
                cases);
    }

    // Ensure no extra content after termination
    inf.readEof();
    return 0;
}
