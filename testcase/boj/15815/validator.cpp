#include "testlib.h"
#include <stack>
#include <string>
#include <cctype>
#include <climits>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the entire expression line (no spaces, length <= 100, non-empty)
    string expr = inf.readLine("[^]+", "expression");
    // Global formatting: only one line, then EOF (no extra blank lines)
    inf.readEof();

    int n = (int)expr.size();
    ensuref(n > 0, "Expression must be non-empty");
    ensuref(n <= 100, "Expression length must be at most 100, got %d", n);

    // Check allowed characters and at least one operator
    int opCount = 0, digitCount = 0;
    for (int i = 0; i < n; ++i) {
        char c = expr[i];
        bool isDigit = (c >= '0' && c <= '9');
        bool isOp = (c == '+' || c == '-' || c == '*' || c == '/');
        ensuref(isDigit || isOp,
                "Invalid character '%c' at position %d (0-based)", c, i);
        if (isDigit) digitCount++;
        if (isOp) opCount++;
    }

    // Problem guarantees "잘못된 수식이 입력되는 경우도 없습니다",
    // but we still validate well-formed postfix:
    // For a single number, opCount == 0 is allowed (trivial expression).
    if (opCount > 0) {
        ensuref(digitCount >= 2, "Non-trivial expression must have at least 2 operands");
        ensuref(digitCount == opCount + 1,
                "In a valid postfix expression, #digits must be #ops + 1, got digits=%d, ops=%d",
                digitCount, opCount);
    }

    // Simulate evaluation to enforce:
    //  - correct postfix structure (enough operands for each op, 1 result at end)
    //  - no division by zero
    //  - all intermediate results are integers within 32-bit signed range
    stack<long long> st;

    auto applyOp = [&](char op, long long a, long long b) -> long long {
        // a (first operand), b (second operand) in usual order for postfix: a op b
        long long res = 0;
        if (op == '+') {
            res = a + b;
        } else if (op == '-') {
            res = a - b;
        } else if (op == '*') {
            res = a * b;
        } else if (op == '/') {
            ensuref(b != 0, "Division by zero in evaluation");
            // C++ integer division truncates toward zero, which is standard
            res = a / b;
        } else {
            ensuref(false, "Unknown operator '%c'", op);
        }
        // Check 32-bit signed range constraint
        ensuref(res >= INT_MIN && res <= INT_MAX,
                "Intermediate result %lld out of 32-bit signed int range", res);
        return res;
    };

    for (int i = 0; i < n; ++i) {
        char c = expr[i];
        if (c >= '0' && c <= '9') {
            // Each digit is a separate integer operand (0-9)
            st.push(c - '0');
        } else {
            // Operator: need two operands
            ensuref((int)st.size() >= 2,
                    "Not enough operands before operator '%c' at position %d", c, i);
            long long b = st.top(); st.pop();
            long long a = st.top(); st.pop();
            long long r = applyOp(c, a, b);
            st.push(r);
        }
    }

    ensuref(!st.empty(), "Evaluation stack empty after processing expression");
    long long finalRes = st.top(); st.pop();
    ensuref(st.empty(), "Extra operands remain after evaluation (invalid postfix expression)");
    ensuref(finalRes >= INT_MIN && finalRes <= INT_MAX,
            "Final result %lld out of 32-bit signed int range", finalRes);

    return 0;
}
