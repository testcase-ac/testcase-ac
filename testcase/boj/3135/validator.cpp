#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 999, "A");
    inf.readSpace();
    int b = inf.readInt(1, 999, "B");
    inf.readEoln();
    ensuref(a != b, "A and B must be different: A=%d, B=%d", a, b);

    int n = inf.readInt(1, 5, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        // CHECK: The statement says preset frequencies are less than 1000,
        // but omits a lower bound; use the same positive frequency domain as A and B.
        inf.readInt(1, 999, "preset");
        inf.readEoln();
    }

    inf.readEof();
}
