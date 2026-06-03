#include "testlib.h"

#include <string>

using namespace std;

namespace {

void validatePositiveInteger(const string& s, int l, int r, const char* name) {
    ensuref(l < r, "%s is empty", name);
    ensuref(s[l] != '0', "%s has leading zero or is not positive", name);
    for (int i = l; i < r; ++i) {
        ensuref('0' <= s[i] && s[i] <= '9', "%s contains a non-digit", name);
    }
}

void validateRangeExpression(const string& line) {
    ensuref(!line.empty(), "range list must not be empty");
    ensuref((int)line.size() <= 1000, "range list is longer than 1000 characters");

    int itemStart = 0;
    int hyphen = -1;
    for (int i = 0; i <= (int)line.size(); ++i) {
        if (i == (int)line.size() || line[i] == ',') {
            ensuref(itemStart < i, "empty print range before position %d", i + 1);
            if (hyphen == -1) {
                validatePositiveInteger(line, itemStart, i, "page");
            } else {
                validatePositiveInteger(line, itemStart, hyphen, "low");
                validatePositiveInteger(line, hyphen + 1, i, "high");
            }
            itemStart = i + 1;
            hyphen = -1;
        } else if (line[i] == '-') {
            ensuref(hyphen == -1, "print range has multiple hyphens before position %d", i + 1);
            hyphen = i;
        } else {
            ensuref('0' <= line[i] && line[i] <= '9',
                    "invalid character at position %d: %c",
                    i + 1,
                    line[i]);
        }
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCase = 1;
    while (true) {
        int n = inf.readInt(0, 1000, "n");
        inf.readEoln();
        if (n == 0) {
            break;
        }

        setTestCase(testCase++);
        string ranges = inf.readLine("[0-9,\\-]{1,1000}", "ranges");
        validateRangeExpression(ranges);
    }

    inf.readEof();
}
