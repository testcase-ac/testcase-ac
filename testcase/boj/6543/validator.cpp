#include "testlib.h"

#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

namespace {

struct Token {
    string value;
    int line;
};

long long parseNonNegativeInt(const Token& token) {
    ensuref(!token.value.empty(), "empty token at line %d", token.line);
    ensuref(token.value == "0" || token.value[0] != '0',
            "non-canonical integer at line %d: %s", token.line,
            token.value.c_str());

    long long result = 0;
    for (char ch : token.value) {
        ensuref(isdigit(static_cast<unsigned char>(ch)),
                "non-integer token at line %d: %s", token.line,
                token.value.c_str());
        result = result * 10 + (ch - '0');
        ensuref(result <= 1000000000LL,
                "integer too large at line %d: %s", token.line,
                token.value.c_str());
    }
    return result;
}

vector<Token> readTokens() {
    vector<Token> tokens;
    int lineNumber = 1;

    while (!inf.eof()) {
        string line = inf.readLine("[^]*", "line");

        bool previousWasSpace = true;
        string current;
        for (char ch : line) {
            ensuref(ch == ' ' || !isspace(static_cast<unsigned char>(ch)),
                    "unsupported whitespace at line %d", lineNumber);
            if (ch == ' ') {
                ensuref(!previousWasSpace,
                        "leading or repeated space at line %d", lineNumber);
                tokens.push_back({current, lineNumber});
                current.clear();
                previousWasSpace = true;
            } else {
                current += ch;
                previousWasSpace = false;
            }
        }

        ensuref(!previousWasSpace || current.empty(),
                "trailing space at line %d", lineNumber);
        if (!current.empty()) {
            tokens.push_back({current, lineNumber});
        }

        ++lineNumber;
    }

    inf.readEof();
    return tokens;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<Token> tokens = readTokens();
    ensuref(!tokens.empty(), "input must contain the terminating 0");

    size_t pos = 0;
    int testCaseCount = 0;
    long long scalarTokenCount = 0;

    while (true) {
        ensuref(pos < tokens.size(), "missing terminating 0");
        int n = static_cast<int>(parseNonNegativeInt(tokens[pos++]));
        ++scalarTokenCount;

        if (n == 0) {
            ensuref(pos == tokens.size(), "extra tokens after terminating 0");
            break;
        }

        ++testCaseCount;
        setTestCase(testCaseCount);
        ensuref(testCaseCount <= 100000,
                "too many test cases: %d", testCaseCount);  // CHECK: statement gives no test-case limit.

        ensuref(1 <= n && n <= 5000, "n out of range: %d", n);
        ensuref(pos < tokens.size(), "missing m for test case %d", testCaseCount);
        int m = static_cast<int>(parseNonNegativeInt(tokens[pos++]));
        ++scalarTokenCount;
        ensuref(0 <= m && m <= 100000, "m out of range: %d", m);

        for (int i = 1; i <= m; ++i) {
            ensuref(pos + 1 < tokens.size(),
                    "missing endpoint for edge %d in test case %d", i,
                    testCaseCount);
            int from = static_cast<int>(parseNonNegativeInt(tokens[pos++]));
            int to = static_cast<int>(parseNonNegativeInt(tokens[pos++]));
            scalarTokenCount += 2;

            ensuref(1 <= from && from <= n,
                    "edge %d has from endpoint out of range: %d", i, from);
            ensuref(1 <= to && to <= n,
                    "edge %d has to endpoint out of range: %d", i, to);
        }

        ensuref(scalarTokenCount < 5000000LL,
                "input has too many scalar tokens");  // CHECK: practical cap because the statement gives no total input limit.
    }

    ensuref(scalarTokenCount < 5000000LL,
            "input has too many scalar tokens");  // CHECK: practical cap because the statement gives no total input limit.
}
