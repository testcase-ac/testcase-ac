#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

namespace {

const double PI = acos(-1.0);

bool isStandardDecimal(const string& s) {
    int pos = 0;
    if (pos < (int)s.size() && (s[pos] == '-' || s[pos] == '+')) {
        ++pos;
    }

    bool sawDigit = false;
    bool sawDot = false;
    int digitCount = 0;
    for (; pos < (int)s.size(); ++pos) {
        char c = s[pos];
        if (isdigit((unsigned char)c)) {
            sawDigit = true;
            ++digitCount;
            continue;
        }
        if (c == '.' && !sawDot) {
            sawDot = true;
            continue;
        }
        return false;
    }

    return sawDigit && digitCount <= 10;
}

double readDecimal(double minValue, double maxValue, bool minInclusive,
                   bool maxInclusive, const string& name) {
    string token = inf.readToken("[^ \n\r\t]+", name);
    ensuref(isStandardDecimal(token), "%s must be standard decimal notation with at most 10 digits: %s",
            name.c_str(), token.c_str());

    double value = stod(token);
    bool aboveMin = minInclusive ? value >= minValue : value > minValue;
    bool belowMax = maxInclusive ? value <= maxValue : value < maxValue;
    ensuref(aboveMin && belowMax, "%s out of bounds: %.17g", name.c_str(), value);
    return value;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseIndex = 1;
    while (!inf.seekEof()) {
        int n = inf.readInt(0, 8, "n");
        inf.readEoln();
        if (n == 0) {
            inf.readEof();
            return 0;
        }

        double guideSpeed = readDecimal(1.0, 100.0, false, true, "guide_speed");
        inf.readEoln();

        for (int i = 0; i < n; ++i) {
            readDecimal(-1e6, 1e6, true, true,
                        format("x_%d_%d", caseIndex, i + 1));
            inf.readSpace();
            readDecimal(-1e6, 1e6, true, true,
                        format("y_%d_%d", caseIndex, i + 1));
            inf.readSpace();
            double personSpeed = readDecimal(1.0, 100.0, true, false,
                                             format("person_speed_%d_%d", caseIndex, i + 1));
            ensuref(personSpeed < guideSpeed,
                    "person speed must be less than guide speed in case %d person %d",
                    caseIndex, i + 1);
            inf.readSpace();
            readDecimal(0.0, 2.0 * PI, true, false,
                        format("angle_%d_%d", caseIndex, i + 1));
            inf.readEoln();
        }

        ++caseIndex;
        // CHECK: the English original uses a terminating n = 0, but the
        // existing testcase providers and accepted solution also allow EOF
        // after a complete case.
    }

    ensuref(caseIndex > 1, "at least one test case is required");
    inf.readEof();
    return 0;
}
