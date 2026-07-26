#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int s = inf.readInt(2, 1000000000, "s_i");
        inf.readSpace();
        int c = inf.readInt(1, 999999999, "c_i");
        inf.readEoln();
        ensuref(c < s, "box %d violates c_i < s_i: c_i=%d, s_i=%d", i, c, s);
    }

    inf.readEof();
    return 0;
}
