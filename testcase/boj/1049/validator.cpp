#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 50, "m");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        int packagePrice = inf.readInt(0, 1000, "package_price");
        inf.readSpace();
        int singlePrice = inf.readInt(0, 1000, "single_price");
        inf.readEoln();
        (void)packagePrice;
        (void)singlePrice;
    }

    (void)n;
    inf.readEof();
}
