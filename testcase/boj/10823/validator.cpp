#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<string> lines;
    string s;
    while (!inf.eof()) {
        string line = inf.readLine("[0-9,]+", "S_line");
        lines.push_back(line);
        s += line;
        ensuref(s.size() <= 10000, "S length exceeds 10000");
    }

    ensuref(!lines.empty(), "S must contain at least one line");
    ensuref(!s.empty(), "S must not be empty");
    ensuref(isdigit((unsigned char)s.front()), "S must start with a digit");
    ensuref(isdigit((unsigned char)s.back()), "S must end with a digit");

    long long value = 0;
    int digitCount = 0;
    for (int i = 0; i <= (int)s.size(); ++i) {
        if (i == (int)s.size() || s[i] == ',') {
            ensuref(digitCount > 0, "empty number before position %d", i + 1);
            ensuref(value >= 1 && value <= 1000000,
                    "number ending at position %d is out of range: %lld",
                    i, value);
            value = 0;
            digitCount = 0;
            continue;
        }

        ensuref(isdigit((unsigned char)s[i]), "invalid character at position %d", i + 1);
        value = value * 10 + (s[i] - '0');
        ensuref(value <= 1000000, "number exceeds 1000000 before position %d", i + 1);
        ++digitCount;
    }

    inf.readEof();
    return 0;
}
