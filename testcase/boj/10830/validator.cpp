#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 5, "n");
    inf.readSpace();
    long long b = inf.readLong(1LL, 100000000000LL, "b");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(0, 1000, "a_ij");
        }
        inf.readEoln();
    }

    inf.readEof();
}
