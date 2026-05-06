#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    bool hasX = false;
    for (int i = 0; i < N; ++i) {
        string s = inf.readToken("[OX]{1,100}", "S_i");
        ensuref((int)s.size() == M,
                "Length of S_%d is %d, expected %d", i + 1, (int)s.size(), M);
        inf.readEoln();
        for (char c : s)
            if (c == 'X') hasX = true;
    }

    ensuref(hasX, "At least one S_i must contain 'X'");

    inf.readEof();
}
