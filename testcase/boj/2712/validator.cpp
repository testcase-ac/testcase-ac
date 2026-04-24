#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; tc++) {
        // Read the value as a raw token, then validate format
        string val = inf.readToken("[^]+", "value");
        // Must consist of digits and at most one dot
        int dotCount = 0;
        for (char c : val) {
            if (c == '.') {
                dotCount++;
            } else {
                ensuref(isdigit(c), "Invalid character '%c' in value: %s", c, val.c_str());
            }
        }
        ensuref(dotCount <= 1, "Too many decimal points in value: %s", val.c_str());
        if (dotCount == 1) {
            size_t p = val.find('.');
            // At least one digit before and after the dot
            ensuref(p > 0, "Missing digits before decimal point in value: %s", val.c_str());
            ensuref(p + 1 < val.size(), "Missing digits after decimal point in value: %s", val.c_str());
            // No more than 4 digits after decimal
            ensuref((int)(val.size() - p - 1) <= 4,
                    "Too many digits after decimal point in value: %s", val.c_str());
        }
        // We choose to disallow a leading '+' or '-' since problem implies non-negative quantities
        ensuref(val[0] != '+' && val[0] != '-',
                "Signed values not allowed: %s", val.c_str());

        inf.readSpace();

        // Read unit token and validate it's one of the four allowed
        string unit = inf.readToken("[a-z]+", "unit");
        bool okUnit = (unit == "kg" || unit == "lb" || unit == "l" || unit == "g");
        ensuref(okUnit, "Invalid unit '%s'; must be one of kg, lb, l, g", unit.c_str());

        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
