#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 99, "M");
    ensuref(m % 2 == 1, "M must be odd: %d", m);
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string votes = inf.readToken("[OX]{1,99}", "votes");
        ensuref((int)votes.size() == m,
                "votes length at row %d must be M=%d, got %d",
                i + 1,
                m,
                (int)votes.size());
        inf.readEoln();
    }

    inf.readEof();
}
