#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cnt = 0;
    // Read lines until a line with "0" appears
    while (true) {
        // Read an entire line consisting of one or more digits (no spaces)
        string s = inf.readLine("[0-9]+", "line");
        int len = (int)s.length();
        // Length must be between 1 and 5
        ensuref(len >= 1 && len <= 5,
                "Each line must contain 1 to 5 digits, got \"%s\" of length %d",
                s.c_str(), len);
        // No leading zeros allowed, except the single character "0"
        if (len > 1) {
            ensuref(s[0] != '0',
                    "Leading zeros are not allowed, but got \"%s\"",
                    s.c_str());
        }
        // Parse the integer value
        int v = 0;
        for (char c : s) {
            v = v * 10 + (c - '0');
        }
        // Must be in [0, 99999]
        ensuref(v >= 0 && v <= 99999,
                "Value must be between 0 and 99999, got %d from \"%s\"",
                v, s.c_str());
        // If it's the terminator "0", stop reading further test cases
        if (v == 0) {
            break;
        }
        // Otherwise it must be a valid test case in [1, 99999]
        ensuref(v >= 1 && v <= 99999,
                "Test case number must be between 1 and 99999, got %d",
                v);
        cnt++;
        // As per validator rules, assume at most 100000 test cases
        ensuref(cnt <= 100000,
                "Too many test cases: %d (maximum allowed is 100000)",
                cnt);
    }

    // No extra data after the terminating "0" line
    inf.readEof();
    return 0;
}
