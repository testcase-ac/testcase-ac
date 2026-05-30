#include "testlib.h"
#include <string>
using namespace std;

static const int MAX_POWER = 10000;

void validateBigInt(const string &s, const char *name) {
    bool negative = (s[0] == '-');
    const string digits = s.substr(negative ? 1 : 0);

    ensuref(!digits.empty(), "%s: missing digits", name);
    ensuref(digits == "0" || digits[0] != '0', "%s: leading zeroes are not canonical", name);
    ensuref(!negative || digits != "0", "%s: -0 is not canonical", name);

    ensuref((int)digits.size() <= MAX_POWER + 1,
            "%s: too many digits (%d) > %d",
            name, (int)digits.size(), MAX_POWER + 1);

    if ((int)digits.size() == MAX_POWER + 1) {
        static string bound = string("1") + string(MAX_POWER, '0');
        ensuref(digits <= bound,
                "%s: absolute value exceeds 10^%d",
                name, MAX_POWER);
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string A = inf.readToken("-?[0-9]+", "A");
    inf.readSpace();
    string B = inf.readToken("-?[0-9]+", "B");
    inf.readEoln();

    validateBigInt(A, "A");
    validateBigInt(B, "B");

    inf.readEof();
    return 0;
}
