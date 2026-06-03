#include "testlib.h"

#include <string>

using namespace std;

const int MAX_TESTS = 100000;
const int MAX_TOTAL_VALUES = 5000000;

int readPart(const string& s, int l, int r, const char* name) {
    ensuref(l < r, "empty %s", name);
    ensuref(r - l == 1 || s[l] != '0', "%s has leading zero: %s", name, s.c_str());

    int value = 0;
    for (int i = l; i < r; ++i) {
        ensuref('0' <= s[i] && s[i] <= '9', "invalid character in %s: %s", name, s.c_str());
        value = value * 10 + (s[i] - '0');
    }
    return value;
}

void validateFractionLine(const string& s, int testIndex, int valueIndex) {
    ensuref(!s.empty(), "empty rational at test %d value %d", testIndex, valueIndex);

    int comma = -1;
    int slash = -1;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] == ',') {
            ensuref(comma == -1, "multiple commas in rational at test %d value %d: %s",
                    testIndex, valueIndex, s.c_str());
            comma = i;
        } else if (s[i] == '/') {
            ensuref(slash == -1, "multiple slashes in rational at test %d value %d: %s",
                    testIndex, valueIndex, s.c_str());
            slash = i;
        } else {
            ensuref('0' <= s[i] && s[i] <= '9',
                    "invalid character in rational at test %d value %d: %s",
                    testIndex, valueIndex, s.c_str());
        }
    }

    int w = 0;
    int n = 0;
    int d = 1;
    if (comma != -1) {
        ensuref(slash != -1 && comma < slash,
                "mixed rational must have form w,n/d at test %d value %d: %s",
                testIndex, valueIndex, s.c_str());
        w = readPart(s, 0, comma, "w");
        n = readPart(s, comma + 1, slash, "n");
        d = readPart(s, slash + 1, (int)s.size(), "d");
    } else if (slash != -1) {
        n = readPart(s, 0, slash, "n");
        d = readPart(s, slash + 1, (int)s.size(), "d");
    } else {
        w = readPart(s, 0, (int)s.size(), "w");
    }

    ensuref(0 <= w && w < 1000, "w out of range at test %d value %d: %d",
            testIndex, valueIndex, w);
    ensuref(0 <= n && n < 1000, "n out of range at test %d value %d: %d",
            testIndex, valueIndex, n);
    ensuref(1 <= d && d < 1000, "d out of range at test %d value %d: %d",
            testIndex, valueIndex, d);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCount = 0;
    int totalValues = 0;
    while (true) {
        int n = inf.readInt(0, 999, "n");
        inf.readEoln();
        if (n == 0) {
            break;
        }

        ++testCount;
        // CHECK: The statement gives no test-count limit; use local practical caps.
        ensuref(testCount <= MAX_TESTS, "too many tests: %d", testCount);
        totalValues += n;
        ensuref(totalValues <= MAX_TOTAL_VALUES, "too many rational values: %d", totalValues);

        setTestCase(testCount);
        for (int i = 1; i <= n; ++i) {
            string rational = inf.readLine("[0-9,/]{1,11}", "rational");
            validateFractionLine(rational, testCount, i);
        }
    }

    inf.readEof();
}
