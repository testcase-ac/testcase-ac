#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n - 1, "K");
    inf.readEoln();
    (void)k;

    for (int i = 2; i <= n; ++i) {
        int p = inf.readInt(1, i - 1, "P_i");
        inf.readSpace();
        long long w = inf.readLong(0LL, 1000000000LL, "W_i");
        inf.readEoln();
        (void)p;
        (void)w;
    }

    inf.readEof();
    return 0;
}
