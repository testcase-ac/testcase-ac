#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int parseOperand(const string& s, int lineIndex, const char* side) {
    ensuref(!s.empty(), "empty %s operand on problem line %d", side, lineIndex);
    ensuref(s == "0" || s[0] != '0',
            "leading zero in %s operand on problem line %d", side, lineIndex);

    int value = 0;
    for (char c : s) {
        ensuref('0' <= c && c <= '9',
                "non-digit character in %s operand on problem line %d", side, lineIndex);
        value = value * 10 + (c - '0');
        ensuref(value <= 1000,
                "%s operand exceeds 1000 on problem line %d", side, lineIndex);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string problem = inf.readLine("[^\\n\\r]*", "problem");
        if (problem == "P=NP") {
            continue;
        }

        size_t plus = problem.find('+');
        ensuref(plus != string::npos, "missing plus sign on problem line %d", i);
        ensuref(problem.find('+', plus + 1) == string::npos,
                "multiple plus signs on problem line %d", i);

        parseOperand(problem.substr(0, plus), i, "left");
        parseOperand(problem.substr(plus + 1), i, "right");
    }

    inf.readEof();
    return 0;
}
