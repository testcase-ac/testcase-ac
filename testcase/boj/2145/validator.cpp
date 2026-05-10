#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    bool seenZero = false;

    while (!inf.eof()) {
        // Read next line as a token (a number string) or detect EOF
        // Each line should contain exactly one token (the number).
        // We'll read the token, then enforce end-of-line.
        if (inf.eof()) break;

        // Read the number as a token consisting of digits only
        string s = inf.readToken("[0-9]+", "N");
        inf.readEoln();

        // Canonical form: no leading zeros except the single "0"
        if (s.size() > 1) {
            ensuref(s[0] != '0', "Number has leading zeros: %s", s.c_str());
        }

        // Convert to integer safely and check range
        // N is a positive integer less than 100000, except the final 0 line.
        long long val = 0;
        for (char c : s) {
            val = val * 10 + (c - '0');
            ensuref(val <= 100000LL, "Number exceeds 100000: %s", s.c_str());
        }

        if (s == "0") {
            // "0" must be the last line
            ensuref(!seenZero, "Multiple terminating zeros are not allowed");
            seenZero = true;
            // After zero, there must be no more data
            ensuref(inf.eof(), "Extra data after terminating zero");
            break;
        } else {
            // Positive integer line; must satisfy 1 <= N < 100000
            ensuref(val >= 1 && val < 100000,
                    "N must be positive and less than 100000, got %lld", val);
            // Also ensure that zero hasn't already appeared before
            ensuref(!seenZero, "Non-zero number appears after terminating zero");
        }
    }

    // File must contain at least one line with "0"
    ensuref(seenZero, "Input must end with a line containing single 0");

    inf.readEof();
}
