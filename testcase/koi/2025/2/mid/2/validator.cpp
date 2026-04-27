#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "N");
    inf.readSpace();
    inf.readInt(1, n, "K");
    inf.readSpace();
    inf.readInt(1, 1000000, "C");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 1000000, "A_i");
        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
