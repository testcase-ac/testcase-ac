#include "testlib.h"

#include <string>

using namespace std;

namespace {

const int kMaxDepth = 16;
const int kMaxLineLength = 786429;
const long long kMaxWeight = 999999999LL;

void parseExpr(const string& s, int& pos, int rodDepth) {
    ensuref(pos < (int)s.size(), "unexpected end of expression");

    if (s[pos] == '[') {
        ensuref(rodDepth < kMaxDepth, "rod depth exceeds %d", kMaxDepth);
        ++pos;
        parseExpr(s, pos, rodDepth + 1);
        ensuref(pos < (int)s.size() && s[pos] == ',',
                "expected comma at position %d", pos + 1);
        ++pos;
        parseExpr(s, pos, rodDepth + 1);
        ensuref(pos < (int)s.size() && s[pos] == ']',
                "expected closing bracket at position %d", pos + 1);
        ++pos;
        return;
    }

    ensuref(s[pos] >= '1' && s[pos] <= '9',
            "weight must be a positive canonical integer at position %d", pos + 1);
    long long weight = 0;
    while (pos < (int)s.size() && s[pos] >= '0' && s[pos] <= '9') {
        weight = weight * 10 + (s[pos] - '0');
        ensuref(weight <= kMaxWeight, "weight is at least 10^9");
        ++pos;
    }
}

void validateLine(const string& line) {
    ensuref(!line.empty(), "mobile expression must not be empty");
    ensuref((int)line.size() <= kMaxLineLength, "mobile expression is too long");

    int pos = 0;
    parseExpr(line, pos, 0);
    ensuref(pos == (int)line.size(), "extra characters at position %d", pos + 1);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);
        string line = inf.readLine();
        validateLine(line);
    }

    inf.readEof();
}
