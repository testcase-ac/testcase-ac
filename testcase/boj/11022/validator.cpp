#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for T; use the local default cap.
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        inf.readInt(1, 9, "A");
        inf.readSpace();
        inf.readInt(1, 9, "B");
        inf.readEoln();
    }

    inf.readEof();
}
