#include "testlib.h"

#include <string>

using namespace std;

bool isWhitespace(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t' || ch == '\v' || ch == '\f';
}

string readWhitespaceSeparatedToken(bool requireLeadingWhitespace, const char* name) {
    if (requireLeadingWhitespace) {
        ensuref(!inf.eof() && isWhitespace(inf.curChar()), "expected whitespace before %s", name);
    }
    inf.skipBlanks();
    ensuref(!inf.eof(), "expected token %s", name);

    string token;
    while (!inf.eof() && !isWhitespace(inf.curChar())) {
        token += inf.nextChar();
    }
    ensuref(!token.empty(), "expected token %s", name);
    return token;
}

int parseUnsignedToken(const string& token, int minValue, int maxValue, const char* name) {
    ensuref(!token.empty(), "%s is empty", name);
    ensuref(token[0] >= '1' && token[0] <= '9', "%s must be a positive canonical integer: %s", name, token.c_str());
    ensuref(token.size() == 1 || token[0] != '0', "%s has leading zero: %s", name, token.c_str());

    long long value = 0;
    for (char ch : token) {
        ensuref(ch >= '0' && ch <= '9', "%s contains a non-digit: %s", name, token.c_str());
        value = value * 10 + (ch - '0');
        ensuref(value <= maxValue, "%s exceeds maximum %d: %s", name, maxValue, token.c_str());
    }
    ensuref(value >= minValue, "%s is below minimum %d: %s", name, minValue, token.c_str());
    return (int)value;
}

int parseLiteral(const string& token, int n, const char* name) {
    ensuref(token.size() >= 2, "%s is too short: %s", name, token.c_str());
    ensuref(token[0] == '+' || token[0] == '-', "%s must start with + or -: %s", name, token.c_str());
    string index = token.substr(1);
    return parseUnsignedToken(index, 1, n, name);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 1000;
    const int MAX_M = 1000000;
    const int MAX_CASES = 100000; // CHECK: statement uses EOF termination and gives no case-count bound.

    int cases = 0;
    while (!inf.seekEof()) {
        ++cases;
        ensuref(cases <= MAX_CASES, "too many test cases: %d", cases);
        setTestCase(cases);

        string nToken = readWhitespaceSeparatedToken(false, "N");
        int n = parseUnsignedToken(nToken, 1, MAX_N, "N");

        string mToken = readWhitespaceSeparatedToken(true, "M");
        int m = parseUnsignedToken(mToken, 1, MAX_M, "M");

        for (int answer = 1; answer <= m; ++answer) {
            string first = readWhitespaceSeparatedToken(true, "first_literal");
            string second = readWhitespaceSeparatedToken(true, "second_literal");
            parseLiteral(first, n, "first_literal");
            parseLiteral(second, n, "second_literal");
        }
    }

    ensuref(cases > 0, "input must contain at least one test case");
    inf.readEof();
}
