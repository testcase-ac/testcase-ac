#include "testlib.h"
#include <stack>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct BigInt {
    bool neg = false;
    string mag = "0";
};

static string trimZeros(string s) {
    size_t pos = s.find_first_not_of('0');
    if (pos == string::npos) return "0";
    return s.substr(pos);
}

static BigInt normalize(BigInt x) {
    x.mag = trimZeros(x.mag);
    if (x.mag == "0") x.neg = false;
    return x;
}

static int cmpAbs(const string& a, const string& b) {
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    if (a == b) return 0;
    return a < b ? -1 : 1;
}

static string addAbs(const string& a, const string& b) {
    string out;
    int carry = 0;
    for (int i = (int)a.size() - 1, j = (int)b.size() - 1; i >= 0 || j >= 0 || carry; --i, --j) {
        int sum = carry;
        if (i >= 0) sum += a[i] - '0';
        if (j >= 0) sum += b[j] - '0';
        out.push_back(char('0' + sum % 10));
        carry = sum / 10;
    }
    reverse(out.begin(), out.end());
    return out;
}

static string subAbs(string a, const string& b) {
    string out;
    int borrow = 0;
    for (int i = (int)a.size() - 1, j = (int)b.size() - 1; i >= 0; --i, --j) {
        int diff = (a[i] - '0') - borrow - (j >= 0 ? b[j] - '0' : 0);
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        out.push_back(char('0' + diff));
    }
    reverse(out.begin(), out.end());
    return trimZeros(out);
}

static BigInt addBig(BigInt a, BigInt b) {
    BigInt out;
    if (a.neg == b.neg) {
        out.neg = a.neg;
        out.mag = addAbs(a.mag, b.mag);
    } else if (cmpAbs(a.mag, b.mag) >= 0) {
        out.neg = a.neg;
        out.mag = subAbs(a.mag, b.mag);
    } else {
        out.neg = b.neg;
        out.mag = subAbs(b.mag, a.mag);
    }
    return normalize(out);
}

static BigInt negBig(BigInt x) {
    if (x.mag != "0") x.neg = !x.neg;
    return x;
}

static BigInt mulBig(BigInt a, BigInt b) {
    vector<int> digits(a.mag.size() + b.mag.size());
    for (int i = (int)a.mag.size() - 1; i >= 0; --i) {
        for (int j = (int)b.mag.size() - 1; j >= 0; --j) {
            digits[i + j + 1] += (a.mag[i] - '0') * (b.mag[j] - '0');
        }
    }
    for (int i = (int)digits.size() - 1; i > 0; --i) {
        digits[i - 1] += digits[i] / 10;
        digits[i] %= 10;
    }
    string mag;
    for (int d : digits) mag.push_back(char('0' + d));
    return normalize({a.neg != b.neg, mag});
}

static BigInt divBig(BigInt a, BigInt b) {
    ensuref(b.mag != "0", "Division by zero in evaluation");
    string q;
    string rem = "0";
    for (char c : a.mag) {
        rem = trimZeros(rem + c);
        int digit = 0;
        while (cmpAbs(rem, b.mag) >= 0) {
            rem = subAbs(rem, b.mag);
            ++digit;
        }
        q.push_back(char('0' + digit));
    }
    ensuref(rem == "0", "Division produced a non-integer intermediate result");
    return normalize({a.neg != b.neg, q});
}

static bool exceedsUpperBound(const BigInt& x) {
    return !x.neg && cmpAbs(x.mag, "2147483647") > 0;
}

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
    //  - all intermediate results are integers not exceeding 2147483647
    stack<BigInt> st;

    auto applyOp = [&](char op, BigInt a, BigInt b) -> BigInt {
        // a (first operand), b (second operand) in usual order for postfix: a op b
        BigInt res;
        if (op == '+') {
            res = addBig(a, b);
        } else if (op == '-') {
            res = addBig(a, negBig(b));
        } else if (op == '*') {
            res = mulBig(a, b);
        } else if (op == '/') {
            res = divBig(a, b);
        } else {
            ensuref(false, "Unknown operator '%c'", op);
        }
        ensuref(!exceedsUpperBound(res),
                "Intermediate result exceeds 2147483647");
        return res;
    };

    for (int i = 0; i < n; ++i) {
        char c = expr[i];
        if (c >= '0' && c <= '9') {
            // Each digit is a separate integer operand (0-9)
            st.push({false, string(1, c)});
        } else {
            // Operator: need two operands
            ensuref((int)st.size() >= 2,
                    "Not enough operands before operator '%c' at position %d", c, i);
            BigInt b = st.top(); st.pop();
            BigInt a = st.top(); st.pop();
            BigInt r = applyOp(c, a, b);
            st.push(r);
        }
    }

    ensuref(!st.empty(), "Evaluation stack empty after processing expression");
    BigInt finalRes = st.top(); st.pop();
    ensuref(st.empty(), "Extra operands remain after evaluation (invalid postfix expression)");
    ensuref(!exceedsUpperBound(finalRes),
            "Final result exceeds 2147483647");

    return 0;
}
