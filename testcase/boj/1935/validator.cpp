#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 26, "N");
    inf.readEoln();

    // Read postfix expression
    string expr = inf.readToken("[A-Z+\\-*/]{1,100}", "expr");
    inf.readEoln();
    int L = expr.size();
    // Check that only allowed operand letters appear, and operators are valid
    for (int i = 0; i < L; i++) {
        char c = expr[i];
        if (c >= 'A' && c <= 'Z') {
            int idx = c - 'A';
            ensuref(idx < N, "Operand '%c' at position %d is out of range A..%c", c, i, char('A' + N - 1));
        } else {
            // Must be one of + - * /
            ensuref(c=='+'||c=='-'||c=='*'||c=='/', "Invalid operator '%c' at position %d", c, i);
        }
    }

    // Read values for A, B, ..., up to N operands
    vector<double> val(N);
    for (int i = 0; i < N; i++) {
        // natural number <= 100
        int v = inf.readInt(1, 100, "val_i");
        inf.readEoln();
        val[i] = v;
    }

    // Simulate postfix evaluation to check stack behavior and intermediate bounds
    vector<double> stack;
    stack.reserve(L);
    const double BOUND = 2000000000.0;
    for (int i = 0; i < L; i++) {
        char c = expr[i];
        if (c >= 'A' && c <= 'Z') {
            // push operand value
            stack.push_back(val[c - 'A']);
        } else {
            // operator: need two operands
            ensuref((int)stack.size() >= 2,
                    "Stack underflow at operator '%c' position %d: need 2 but have %d",
                    c, i, (int)stack.size());
            double b = stack.back(); stack.pop_back();
            double a = stack.back(); stack.pop_back();
            double res = 0.0;
            if (c == '+') {
                res = a + b;
            } else if (c == '-') {
                res = a - b;
            } else if (c == '*') {
                res = a * b;
            } else if (c == '/') {
                ensuref(b != 0.0,
                        "Division by zero at operator '/' position %d", i);
                res = a / b;
            }
            // Check intermediate result bounds
            ensuref(res >= -BOUND && res <= BOUND,
                    "Intermediate result %.10f at position %d out of allowed range [-2e9,2e9]",
                    res, i);
            stack.push_back(res);
        }
    }
    // After full evaluation, exactly one value must remain
    ensuref((int)stack.size() == 1,
            "After evaluation stack has %d elements, expected 1", (int)stack.size());
    // Final result also within bounds
    double final_res = stack.back();
    ensuref(final_res >= -BOUND && final_res <= BOUND,
            "Final result %.10f out of allowed range [-2e9,2e9]", final_res);

    inf.readEof();
    return 0;
}
