#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

string readDigitString(int n, const char* name) {
    string s = inf.readToken("[0-9]+", name);
    inf.readEoln();
    ensuref((int)s.size() == n,
            "%s must have exactly %d digits, but has %d", name, n, (int)s.size());
    return s;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 300000;
    const int MAXQ = 300000;

    int N = inf.readInt(1, MAXN, "N");
    inf.readSpace();
    int Q = inf.readInt(1, MAXQ, "Q");
    inf.readEoln();

    string A = readDigitString(N, "A");
    string B = readDigitString(N, "B");

    for (int qi = 0; qi < Q; ++qi) {
        // Query format: <which> <i> <d>\n
        char which = inf.readChar();
        ensuref(which == 'A' || which == 'B',
                "Query %d: first token must be 'A' or 'B', got '%c'", qi + 1, which);
        inf.readSpace();

        int i = inf.readInt(1, N, "i");
        inf.readSpace();
        int d = inf.readInt(0, 9, "d");
        inf.readEoln();
    }

    inf.readEof();
}
