#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;
    const int MAXK = 200000;

    int N = inf.readInt(1, MAXN, "N");
    inf.readSpace();
    int K = inf.readInt(1, MAXK, "K");
    inf.readEoln();

    // initial colors: all 'W' (white)
    vector<char> color(N + 1, 'W');

    // allowed color IDs
    auto isValidColor = [](char c) {
        return c=='K' || c=='R' || c=='G' || c=='B' ||
               c=='Y' || c=='C' || c=='P' || c=='W';
    };

    for (int qi = 0; qi < K; ++qi) {
        char type = inf.readChar();
        ensuref(type == 'Q' || type == 'U',
                "Query type at line %d must be 'Q' or 'U', found '%c'",
                qi + 2, type);
        if (type == 'Q') {
            inf.readSpace();
            int i = inf.readInt(1, N, "i");
            inf.readSpace();
            int j = inf.readInt(1, N, "j");
            inf.readEoln();
            ensuref(i <= j,
                    "For query Q at line %d, must have i <= j, got i=%d, j=%d",
                    qi + 2, i, j);
        } else { // type == 'U'
            inf.readSpace();
            int idx = inf.readInt(1, N, "i");
            inf.readSpace();
            string s = inf.readToken("[A-Z]", "X");
            inf.readEoln();
            ensuref(s.size() == 1, "Color ID length must be 1");
            char c = s[0];
            ensuref(isValidColor(c),
                    "Invalid color '%c' at update line %d; must be one of K,R,G,B,Y,C,P,W",
                    c, qi + 2);
            // apply update to keep internal state consistent
            color[idx] = c;
        }
    }

    inf.readEof();
}
