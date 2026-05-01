#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const long long MAXV = 500;

string toLiteral(long long x) {
    if (x >= 0) {
        return to_string(x);
    } else {
        long long a = -x;
        return "(0-" + to_string(a) + ")";
    }
}

string genExprWithValue(long long target, int depth);

// Generate an expression with given value and limited depth.
// Ensures: all divisions are exact (integer division) and never divide by zero.
string genExprWithValue(long long target, int depth) {
    if (depth <= 0 || (llabs(target) <= 5 && rnd.next(0, 1) == 0)) {
        return toLiteral(target);
    }

    for (int attempt = 0; attempt < 20; attempt++) {
        int op = rnd.next(0, 3); // 0:+,1:-,2:*,3:/
        long long a = 0, b = 0;

        int leftDepth = 0, rightDepth = 0;
        if (depth - 1 >= 0) {
            leftDepth = rnd.next(0, depth - 1);
            rightDepth = depth - 1 - leftDepth;
        }

        if (op == 0) { // +
            a = rnd.next(-MAXV, MAXV);
            b = target - a;
            if (llabs(b) > MAXV) continue;
        } else if (op == 1) { // -
            a = rnd.next(-MAXV, MAXV);
            b = a - target;
            if (llabs(b) > MAXV) continue;
        } else if (op == 2) { // *
            if (target == 0) {
                a = rnd.next(-10, 10);
                b = 0;
            } else {
                long long at = llabs(target);
                vector<long long> divisors;
                for (long long d = 1; d * d <= at; ++d) {
                    if (at % d == 0) {
                        divisors.push_back(d);
                        if (d * d != at) divisors.push_back(at / d);
                    }
                }
                if (divisors.empty()) continue;
                long long absA = rnd.any(divisors);
                int signTarget = (target > 0 ? 1 : -1);
                int signA = (rnd.next(0, 1) ? 1 : -1);
                int signB = signTarget * signA;
                a = absA * signA;
                b = (at / absA) * signB;
                if (llabs(a) > MAXV || llabs(b) > MAXV) continue;
            }
        } else { // /
            if (target == 0) {
                a = 0;
                long long absB = rnd.next(1, 10);
                if (rnd.next(0, 1)) absB = -absB;
                b = absB;
            } else {
                long long lim = MAXV / llabs(target);
                if (lim <= 0) continue;
                long long absB = rnd.next(1LL, min(10LL, lim));
                if (rnd.next(0, 1)) absB = -absB;
                b = absB;
                a = target * b;
            }
            if (b == 0 || llabs(a) > MAXV || llabs(b) > MAXV) continue;
        }

        string left = genExprWithValue(a, leftDepth);
        string right = genExprWithValue(b, rightDepth);
        char ch = (op == 0 ? '+' : (op == 1 ? '-' : (op == 2 ? '*' : '/')));
        return "(" + left + ch + right + ")";
    }

    return toLiteral(target);
}

string genZeroExpr() {
    int t = rnd.next(0, 3);
    if (t == 0) return "0";
    if (t == 1) return "(0+0)";
    if (t == 2) return "(5-5)";
    return "((1+2)-3)";
}

string genValidExpr() {
    int depth = rnd.next(1, 5);
    long long target = rnd.next(-50, 50);
    return genExprWithValue(target, depth);
}

string genInvalidSyntaxExpr() {
    int method = rnd.next(0, 4);
    if (method == 0) { // leading operator
        string base = genValidExpr();
        char op = rnd.any(string("+-*/"));
        return string(1, op) + base;
    } else if (method == 1) { // two operators in a row
        string left = genValidExpr();
        string right = genValidExpr();
        char op1 = rnd.any(string("+-*/"));
        char op2 = rnd.any(string("+-*/"));
        return left + op1 + op2 + right;
    } else if (method == 2) { // mismatched parentheses
        string base = genValidExpr();
        int v = rnd.next(0, 2);
        if (v == 0) return "(" + base;
        if (v == 1) return base + ")";
        return "(" + base + "))";
    } else if (method == 3) { // empty or malformed parentheses
        int v = rnd.next(0, 1);
        if (v == 0) return "()";
        string base = genValidExpr();
        return "(+" + base + ")";
    } else { // operator at end
        string base = genValidExpr();
        char op = rnd.any(string("+-*/"));
        return base + op;
    }
}

string genDivZeroExpr() {
    string A = genValidExpr();
    string B = genZeroExpr();
    if (rnd.next(0, 1))
        return "(" + A + "/" + B + ")";
    else
        return A + "/" + B;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int dice = rnd.next(0, 9);
    string expr;
    if (dice <= 4) {           // 50%: fully valid expression
        expr = genValidExpr();
    } else if (dice <= 7) {    // 30%: syntactically invalid
        expr = genInvalidSyntaxExpr();
    } else {                   // 20%: division by zero at top level
        expr = genDivZeroExpr();
    }

    println(expr);
    return 0;
}
