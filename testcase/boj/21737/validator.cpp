#include "testlib.h"

#include <string>

using namespace std;

namespace {

const long long kIntMin = -(1LL << 31);
const long long kIntMax = (1LL << 31) - 1;

bool isDigit(char c) {
    return '0' <= c && c <= '9';
}

bool isOperator(char c) {
    return c == 'S' || c == 'M' || c == 'U' || c == 'P' || c == 'C';
}

long long apply(long long lhs, long long rhs, char op) {
    if (op == 0) {
        return lhs;
    }
    if (op == 'S') {
        return lhs - rhs;
    }
    if (op == 'M') {
        return lhs * rhs;
    }
    if (op == 'U') {
        ensuref(rhs != 0, "division by zero");
        return lhs / rhs;
    }
    ensuref(op == 'P', "unexpected operator %c", op);
    return lhs + rhs;
}

void ensureIntRange(long long value, const char* what, int position) {
    ensuref(kIntMin <= value && value <= kIntMax,
            "%s out of signed 32-bit range at position %d: %lld",
            what, position, value);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "n");
    inf.readEoln();

    string expr = inf.readToken("[0-9SMUPC]{1,1000000}", "expression");
    inf.readEoln();
    inf.readEof();

    ensuref(isDigit(expr.front()), "expression must start with a digit");
    ensuref(isOperator(expr.back()), "expression must end with an operator");

    int operatorCount = 0;
    long long lhs = 0;
    long long rhs = 0;
    char pending = 0;
    bool readingRhs = false;
    bool previousBinaryOperator = false;

    for (int i = 0; i < static_cast<int>(expr.size()); ++i) {
        char c = expr[i];
        if (isDigit(c)) {
            long long& current = readingRhs ? rhs : lhs;
            int digit = c - '0';
            ensuref(current <= (kIntMax - digit) / 10,
                    "input number out of signed 32-bit range at position %d",
                    i + 1);
            current = current * 10 + digit;
            ensureIntRange(current, "input number", i + 1);
            previousBinaryOperator = false;
            continue;
        }

        ++operatorCount;

        if (c == 'C') {
            ensuref(!previousBinaryOperator,
                    "C cannot immediately follow S, M, U, or P at position %d",
                    i + 1);
            lhs = apply(lhs, rhs, pending);
            ensureIntRange(lhs, "calculation result", i + 1);
            rhs = 0;
            pending = 0;
            readingRhs = false;
            previousBinaryOperator = false;
            continue;
        }

        ensuref(!previousBinaryOperator,
                "S, M, U, and P cannot be consecutive at position %d",
                i + 1);
        lhs = apply(lhs, rhs, pending);
        ensureIntRange(lhs, "calculation result", i + 1);
        rhs = 0;
        pending = c;
        readingRhs = true;
        previousBinaryOperator = true;
    }

    ensuref(operatorCount == n,
            "n must equal the number of alphabet symbols: expected %d, found %d",
            n, operatorCount);
}
