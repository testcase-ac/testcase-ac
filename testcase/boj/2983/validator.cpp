#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    string dirs = inf.readToken("[ABCD]+", "dirs");
    ensuref((int)dirs.size() == k, "dirs length is %d, expected %d", (int)dirs.size(), k);
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(0, 1000000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 1000000000, "y_i");
        inf.readEoln();
    }
    // CHECK: The statement gives N plant coordinates but does not explicitly say
    // that two plants cannot share the same coordinates, so duplicates are accepted.

    inf.readEof();
}
