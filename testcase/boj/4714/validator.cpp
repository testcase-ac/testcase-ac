#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static long double parseDecimal(const string& s, const char* name) {
    static const regex decimalRe("^-?(0|[1-9][0-9]{0,99})(\\.[0-9]{1,100})?$");
    ensuref(regex_match(s, decimalRe),
            "%s must be a canonical decimal number without leading zeros or plus sign: got '%s'",
            name, s.c_str());

    char* end = nullptr;
    errno = 0;
    long double value = strtold(s.c_str(), &end);
    ensuref(errno != ERANGE && end != nullptr && *end == '\0' && isfinite(value),
            "%s is outside the supported finite decimal range: got '%s'",
            name, s.c_str());

    ensuref(!(s[0] == '-' && value == 0.0L),
            "%s must not be a signed zero: got '%s'", name, s.c_str());
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_WEIGHTS = 100000;

    bool sawTerminator = false;
    int weights = 0;

    while (!inf.seekEof()) {
        string token = inf.readToken("[^ ]{1,202}", "weight");
        inf.readEoln();

        long double value = parseDecimal(token, "weight");
        if (value < 0.0L) {
            sawTerminator = true;
            break;
        }

        ++weights;
        // CHECK: The statement gives no maximum number of weight lines.
        ensuref(weights <= MAX_WEIGHTS,
                "number of weight lines exceeds practical cap %d", MAX_WEIGHTS);
    }

    ensuref(sawTerminator, "input must end with a negative floating point number");
    inf.readEof();
}
