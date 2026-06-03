#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 1000000, "K");
    inf.readEoln();

    ensuref(n <= k, "N must be at most K, got N=%d and K=%d", n, k);

    for (int i = 0; i < n; ++i) {
        inf.readInt(0, 2147483647, "capacity");
        inf.readEoln();
    }

    inf.readEof();
}
