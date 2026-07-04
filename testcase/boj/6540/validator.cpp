#include "testlib.h"

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

int parseNonNegativeInt(const string& token, int maxValue, const char* name) {
    ensuref(!token.empty(), "%s is empty", name);
    ensuref(token == "0" || (token[0] >= '1' && token[0] <= '9'),
            "%s must be a canonical non-negative integer: %s", name, token.c_str());

    long long value = 0;
    for (char ch : token) {
        ensuref(ch >= '0' && ch <= '9', "%s contains a non-digit: %s", name, token.c_str());
        value = value * 10 + (ch - '0');
        ensuref(value <= maxValue, "%s exceeds maximum %d: %s", name, maxValue, token.c_str());
    }
    return (int)value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 200;
    const int MAX_FREQUENCY = 1000000;
    const int MAX_SUM = 1000000;
    const int MAX_CASES = 100000; // CHECK: the statement uses sentinel termination and gives no case-count bound.

    int cases = 0;
    bool needWhitespace = false;
    while (true) {
        string nToken = readWhitespaceSeparatedToken(needWhitespace, "n");
        int n = parseNonNegativeInt(nToken, MAX_N, "n");
        if (n == 0) {
            break;
        }
        needWhitespace = true;

        ++cases;
        ensuref(cases <= MAX_CASES, "too many test cases: %d", cases);
        setTestCase(cases);

        long long sum = 0;
        for (int i = 0; i < 2 * n + 1; ++i) {
            string frequencyToken = readWhitespaceSeparatedToken(true, "frequency");
            int frequency = parseNonNegativeInt(frequencyToken, MAX_FREQUENCY, "frequency");
            sum += frequency;
        }

        ensuref(sum >= 1 && sum <= MAX_SUM,
                "frequency sum must be in [1, %d], got %lld", MAX_SUM, sum);
    }

    ensuref(cases > 0, "input must contain at least one test case");
    inf.skipBlanks();
    inf.readEof();
    return 0;
}
