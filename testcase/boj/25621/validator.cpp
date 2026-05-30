#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

long long readOperand(const string& token, const char* name) {
    ensuref(token.size() >= 2, "%s is missing operand: %s", name, token.c_str());
    ensuref(token[0] == '+' || token[0] == '-' || token[0] == '*',
            "%s has invalid operator: %s", name, token.c_str());

    string value = token.substr(1);
    ensuref(value.size() == 1 || value[0] != '0',
            "%s has leading zeroes: %s", name, token.c_str());

    long long result = 0;
    for (char ch : value) {
        ensuref('0' <= ch && ch <= '9',
                "%s has a non-digit operand: %s", name, token.c_str());
        result = result * 10 + (ch - '0');
        ensuref(result <= 1000000000LL,
                "%s operand is out of range: %s", name, token.c_str());
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readSpace();
    inf.readLong(0, 1000000000LL, "K_0");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string op1 = inf.readToken("[+\\-*][0-9]+", "op1");
        inf.readSpace();
        string op2 = inf.readToken("[+\\-*][0-9]+", "op2");
        inf.readEoln();

        readOperand(op1, "op1");
        readOperand(op2, "op2");
    }

    inf.readEof();
}
