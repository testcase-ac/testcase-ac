#include "testlib.h"

#include <string>

using namespace std;

namespace {

const long long kMaxValue = 1000000000LL;

long long parseNonNegativeInteger(const string& s, int& pos, const char* name, int caseIndex) {
    int start = pos;
    ensuref(pos < (int)s.size() && s[pos] >= '0' && s[pos] <= '9',
            "case %d: %s must start with a digit", caseIndex, name);

    while (pos < (int)s.size() && s[pos] >= '0' && s[pos] <= '9') {
        ++pos;
    }

    string token = s.substr(start, pos - start);
    ensuref(token == "0" || token[0] != '0',
            "case %d: %s has leading zero: %s", caseIndex, name, token.c_str());

    long long value = 0;
    for (char ch : token) {
        value = value * 10 + (ch - '0');
        ensuref(value <= kMaxValue,
                "case %d: %s exceeds 1000000000: %s", caseIndex, name, token.c_str());
    }
    return value;
}

void requireLiteral(const string& s, int& pos, const string& literal, int caseIndex) {
    ensuref(s.compare(pos, literal.size(), literal) == 0,
            "case %d: expected literal '%s' at position %d", caseIndex, literal.c_str(), pos + 1);
    pos += (int)literal.size();
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(1, 100, "P");
    inf.readEoln();

    for (int i = 1; i <= p; ++i) {
        setTestCase(i);
        string equation = inf.readLine("[0-9]{1,10}x\\ \\+\\ [0-9]{1,10}\\ =\\ [0-9]{1,10}", "equation");

        int pos = 0;
        parseNonNegativeInteger(equation, pos, "a", i);
        requireLiteral(equation, pos, "x + ", i);
        parseNonNegativeInteger(equation, pos, "b", i);
        requireLiteral(equation, pos, " = ", i);
        parseNonNegativeInteger(equation, pos, "c", i);
        ensuref(pos == (int)equation.size(), "case %d: trailing characters in equation", i);
    }

    inf.readEof();
}
