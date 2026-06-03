#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for the number of test cases.
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        inf.readLong(1LL, 1000000000LL, "l_t");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "w_t");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "l_e");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "w_e");
        inf.readEoln();
    }

    inf.readEof();
}
