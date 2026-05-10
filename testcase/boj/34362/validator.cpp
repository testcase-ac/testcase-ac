#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single token as a number string; we'll validate format manually.
    string s = inf.readToken("[^]+", "N");
    inf.readEoln();

    // Check overall format of a real number with optional sign and optional decimal part,
    // and at most 4 digits after the decimal point.
    // Regex explanation:
    //  - optional '-' sign
    //  - either:
    //      * "0" with optional fractional part, OR
    //      * non-zero leading digit [1-9] followed by digits, with optional fractional part
    //  - optional: '.' followed by 1 to 4 digits
    //
    // This enforces canonical form (no leading '+', no leading zeros except "0").
    bool ok = false;
    {
        // Manually parse to enforce all rules, since testlib regex is limited.
        int i = 0;
        int n = (int)s.size();

        // Optional '-'
        bool neg = false;
        if (i < n && s[i] == '-') {
            neg = true;
            ++i;
        }

        // There must be at least one digit before decimal point
        ensuref(i < n && s[i] >= '0' && s[i] <= '9',
                "N must have at least one digit before decimal point");

        // Leading zero rules:
        if (s[i] == '0') {
            // integer part is exactly '0'
            ++i;
            // Next char must not be a digit (so no leading zeros like 01)
            ensuref(i == n || s[i] == '.',
                    "N must not contain leading zeros");
        } else {
            // First digit is 1-9
            ++i;
            // Consume remaining integer digits
            while (i < n && s[i] >= '0' && s[i] <= '9') ++i;
        }

        int fracLen = 0;
        if (i < n && s[i] == '.') {
            ++i;
            int startFrac = i;
            while (i < n && s[i] >= '0' && s[i] <= '9') {
                ++i;
                ++fracLen;
            }
            ensuref(fracLen >= 1, "If decimal point is present, it must be followed by digits");
            ensuref(fracLen <= 4, "At most 4 digits are allowed after the decimal point");
        }

        ensuref(i == n, "Invalid characters found in N");

        ok = true;
    }
    ensuref(ok, "Invalid format for N");

    // Convert to double and check range -100000 <= N <= 100000
    // Using testlib's string-to-double is not available directly, so use std::stod.
    // This is safe because we already validated format.
    long double val;
    try {
        val = stold(s);
    } catch (...) {
        ensuref(false, "Failed to parse N as a real number");
    }
    ensuref(val >= -100000.0L && val <= 100000.0L,
            "N is out of range: must be between -100000 and 100000 inclusive");

    inf.readEof();
}
