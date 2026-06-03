#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

namespace {

const int MAX_LINE_LENGTH = 32000;
const int MAX_TEST_CASES = 100000;
const int MAX_TOTAL_EXPRESSION_CHARS = 10000000;

void validateExpression(const string& line, int testCase) {
    ensuref(!line.empty(), "case %d: expression line is empty", testCase);
    ensuref((int)line.size() <= MAX_LINE_LENGTH,
            "case %d: line length %d exceeds %d",
            testCase,
            (int)line.size(),
            MAX_LINE_LENGTH);
    ensuref(line.front() == '(' && line.back() == ')',
            "case %d: expression must be enclosed in parentheses",
            testCase);

    vector<int> childCounts;
    childCounts.reserve(line.size());

    for (int i = 0; i < (int)line.size(); ++i) {
        char c = line[i];
        if (c == '(') {
            if (!childCounts.empty()) {
                ++childCounts.back();
            }
            childCounts.push_back(0);
        } else if (c == 'T' || c == 'F') {
            ensuref(!childCounts.empty(),
                    "case %d: literal at position %d is outside an expression",
                    testCase,
                    i + 1);
            ++childCounts.back();
        } else if (c == ')') {
            ensuref(!childCounts.empty(),
                    "case %d: unmatched closing parenthesis at position %d",
                    testCase,
                    i + 1);
            ensuref(childCounts.back() > 0,
                    "case %d: empty subexpression closes at position %d",
                    testCase,
                    i + 1);
            childCounts.pop_back();
            ensuref(!childCounts.empty() || i == (int)line.size() - 1,
                    "case %d: extra data after top-level expression at position %d",
                    testCase,
                    i + 1);
        } else {
            ensuref(false,
                    "case %d: invalid character '%c' at position %d",
                    testCase,
                    c,
                    i + 1);
        }
    }

    ensuref(childCounts.empty(), "case %d: unclosed expression", testCase);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCases = 0;
    int totalExpressionChars = 0;

    while (!inf.eof()) {
        string line = inf.readLine("[TF()]{2,32000}", "line");
        if (line == "()") {
            ensuref(testCases > 0, "input must contain at least one real test case");
            inf.readEof();
            return 0;
        }

        ++testCases;
        setTestCase(testCases);
        ensuref(testCases <= MAX_TEST_CASES, "too many test cases: %d", testCases);

        totalExpressionChars += (int)line.size();
        // CHECK: The statement only caps each line and not the number of cases; cap total expression text to keep inputs practical.
        ensuref(totalExpressionChars <= MAX_TOTAL_EXPRESSION_CHARS,
                "total expression characters exceed %d",
                MAX_TOTAL_EXPRESSION_CHARS);

        validateExpression(line, testCases);
    }

    ensuref(false, "missing terminating dummy line ()");
}
