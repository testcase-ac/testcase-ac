#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input numbers
    int a = inf.readInt();
    int b = inf.readInt();
    int c = inf.readInt();

    // Read contestant's output as a token (no spaces expected)
    string s = ouf.readToken();

    // Must contain exactly one '='
    int eq_cnt = count(s.begin(), s.end(), '=');
    if (eq_cnt != 1) {
        quitf(_wa, "expected exactly one '=' but found %d", eq_cnt);
    }
    int pos_eq = s.find('=');
    string left = s.substr(0, pos_eq);
    string right = s.substr(pos_eq + 1);
    if (left.empty() || right.empty()) {
        quitf(_wa, "left or right side of '=' is empty");
    }

    // Count arithmetic operators on each side
    string ops = "+-*/";
    int left_ops = 0, right_ops = 0;
    for (char ch : left)  if (ops.find(ch) != string::npos) left_ops++;
    for (char ch : right) if (ops.find(ch) != string::npos) right_ops++;
    if (left_ops + right_ops != 1) {
        quitf(_wa, "expected exactly one arithmetic operator (one of + - * /), found %d on left and %d on right", left_ops, right_ops);
    }

    // Identify which side is the expression and which side is the single number
    bool expr_on_left = (left_ops == 1);
    string expr = expr_on_left ? left : right;
    string num_side = expr_on_left ? right : left;

    // Parse the expression side: find the operator and split operands
    int pos_op = -1;
    char op = '?';
    for (int i = 0; i < (int)expr.size(); i++) {
        if (ops.find(expr[i]) != string::npos) {
            pos_op = i;
            op = expr[i];
            break;
        }
    }
    if (pos_op <= 0 || pos_op + 1 >= (int)expr.size()) {
        quitf(_wa, "invalid expression '%s'", expr.c_str());
    }
    string s1 = expr.substr(0, pos_op);
    string s2 = expr.substr(pos_op + 1);

    // Helper to check a string is a valid non-empty number (no leading '+', '-', no spaces)
    auto checkNum = [&](const string& x) {
        if (x.empty()) return false;
        for (char ch : x) if (!isdigit(ch)) return false;
        return true;
    };
    if (!checkNum(s1) || !checkNum(s2) || !checkNum(num_side)) {
        quitf(_wa, "invalid number format in output");
    }

    // Extract all numbers in the output (in order) and compare with input a,b,c
    vector<string> out_nums;
    {
        string cur;
        for (char ch : s) {
            if (isdigit(ch)) {
                cur.push_back(ch);
            } else {
                if (!cur.empty()) {
                    out_nums.push_back(cur);
                    cur.clear();
                }
            }
        }
        if (!cur.empty()) {
            out_nums.push_back(cur);
            cur.clear();
        }
    }
    if ((int)out_nums.size() != 3) {
        quitf(_wa, "expected 3 numbers in output, found %d", (int)out_nums.size());
    }
    int na = atoi(out_nums[0].c_str());
    int nb = atoi(out_nums[1].c_str());
    int nc = atoi(out_nums[2].c_str());
    if (na != a || nb != b || nc != c) {
        quitf(_wa, "numbers in output (%d, %d, %d) do not match input (%d, %d, %d)",
              na, nb, nc, a, b, c);
    }

    // Convert operands to integers
    long long v1 = atoll(s1.c_str());
    long long v2 = atoll(s2.c_str());
    long long vn = atoll(num_side.c_str());

    // Evaluate the expression
    long long res;
    switch (op) {
        case '+':
            res = v1 + v2;
            break;
        case '-':
            res = v1 - v2;
            break;
        case '*':
            res = v1 * v2;
            break;
        case '/':
            if (v2 == 0) {
                quitf(_wa, "division by zero");
            }
            if (v1 % v2 != 0) {
                quitf(_wa, "non-integer division: %lld / %lld", v1, v2);
            }
            res = v1 / v2;
            break;
        default:
            quitf(_fail, "unexpected operator '%c'", op);
    }

    // Check the equality holds
    if (expr_on_left) {
        if (res != vn) {
            quitf(_wa, "expression '%s' evaluates to %lld but right side is %lld", expr.c_str(), res, vn);
        }
    } else {
        if (res != vn) {
            quitf(_wa, "expression '%s' evaluates to %lld but left side is %lld", expr.c_str(), res, vn);
        }
    }

    // All checks passed
    quitf(_ok, "correct");
    return 0;
}
