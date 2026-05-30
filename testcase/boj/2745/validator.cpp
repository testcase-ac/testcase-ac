#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string n = inf.readToken("[0-9A-Z]+", "N");
    inf.readSpace();
    int b = inf.readInt(2, 36, "B");
    inf.readEoln();

    ensuref(n.size() == 1 || n[0] != '0',
            "N has a leading zero");

    long long value = 0;
    for (int i = 0; i < (int)n.size(); ++i) {
        char c = n[i];
        int digit = isdigit(c) ? c - '0' : c - 'A' + 10;
        ensuref(digit < b,
                "digit '%c' at position %d is invalid for base %d",
                c, i + 1, b);

        ensuref(value <= (1000000000LL - digit) / b,
                "N exceeds 1000000000 in decimal");
        value = value * b + digit;
    }

    inf.readEof();
}
