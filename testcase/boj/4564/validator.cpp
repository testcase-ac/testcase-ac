#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int test_cases = 0;
    // Read lines until we encounter the terminating "0" line
    while (true) {
        // Read S as a token of digits
        string s = inf.readToken("[0-9]+", "S");
        // Ensure the token is the only thing on its line
        inf.readEoln();

        // No leading zeros allowed, except for the single "0"
        ensuref(!(s.size() > 1 && s[0] == '0'),
                "Leading zeros are not allowed in S: \"%s\"", s.c_str());

        // Parse S manually to avoid overflow
        long long val = 0;
        for (char c : s) {
            val = val * 10 + (c - '0');
        }

        // Check bounds: 0 ≤ S ≤ 100000
        ensuref(val >= 0 && val <= 100000,
                "S (%lld) is out of bounds [0,100000]", val);

        // If we see the terminator 0, break (do not count it as a test case)
        if (val == 0) {
            break;
        }

        // Count this as a valid test case
        ++test_cases;
        // Constraint on number of test cases (unspecified means up to 1e5)
        ensuref(test_cases <= 100000,
                "Number of test cases exceeds 100000");
    }

    // After the terminating line, file must end immediately
    inf.readEof();
    return 0;
}
