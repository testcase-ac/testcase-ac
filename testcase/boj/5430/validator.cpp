#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int readArrayValue(int tc, int index, char& delimiter) {
    string token;
    while (true) {
        char ch = inf.readChar();
        if (ch == ',' || ch == ']') {
            delimiter = ch;
            break;
        }
        ensuref('0' <= ch && ch <= '9',
                "test case %d value %d contains invalid character '%c'", tc, index, ch);
        token.push_back(ch);
        ensuref(token.size() <= 3,
                "test case %d value %d has too many digits", tc, index);
    }

    ensuref(!token.empty(), "test case %d value %d is empty", tc, index);
    ensuref(token.size() == 1 || token[0] != '0',
            "test case %d value %d has a leading zero", tc, index);

    int value = 0;
    for (char ch : token) {
        value = value * 10 + (ch - '0');
    }
    ensuref(1 <= value && value <= 100,
            "test case %d value %d is %d, outside [1, 100]", tc, index, value);
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    long long totalProgramLength = 0;
    long long totalArrayLength = 0;

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        string p = inf.readToken("[RD]{1,100000}", "p");
        inf.readEoln();
        totalProgramLength += (long long)p.size();

        int n = inf.readInt(0, 100000, "n");
        inf.readEoln();
        totalArrayLength += n;

        char open = inf.readChar();
        ensuref(open == '[', "test case %d array must start with '['", tc);

        if (n == 0) {
            char close = inf.readChar();
            ensuref(close == ']', "test case %d empty array must be []", tc);
            inf.readEoln();
            continue;
        }

        for (int i = 1; i <= n; ++i) {
            char delimiter = '\0';
            readArrayValue(tc, i, delimiter);
            if (i < n) {
                ensuref(delimiter == ',',
                        "test case %d value %d must be followed by comma", tc, i);
            } else {
                ensuref(delimiter == ']',
                        "test case %d final value must be followed by ']'", tc);
            }
        }
        inf.readEoln();
    }

    ensuref(totalProgramLength <= 700000,
            "sum of program lengths is %lld, greater than 700000", totalProgramLength);
    ensuref(totalArrayLength <= 700000,
            "sum of n is %lld, greater than 700000", totalArrayLength);

    inf.readEof();
    return 0;
}
