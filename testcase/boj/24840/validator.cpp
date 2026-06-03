#include "testlib.h"

#include <string>

using namespace std;

bool isAtMostPowerOfTen(const string& value, int exponent) {
    int maxLength = exponent + 1;
    if ((int)value.size() != maxLength) {
        return (int)value.size() < maxLength;
    }

    if (value[0] != '1') {
        return value[0] < '1';
    }

    for (int i = 1; i < maxLength; ++i) {
        if (value[i] != '0') {
            return false;
        }
    }
    return true;
}

bool isAtMostSmallLimit(const string& value) {
    const string limit = "100000";
    if (value.size() != limit.size()) {
        return value.size() < limit.size();
    }
    return value <= limit;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    int largeCases = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        string n = inf.readToken("[1-9][0-9]{0,123456}", "N");
        inf.readEoln();

        ensuref(isAtMostPowerOfTen(n, 123456),
                "N exceeds 10^123456 in case %d", tc);

        if (!isAtMostSmallLimit(n)) {
            ++largeCases;
            ensuref(largeCases <= 10,
                    "more than 10 cases exceed 10^5: first violation at case %d", tc);
        }
    }

    inf.readEof();
}
