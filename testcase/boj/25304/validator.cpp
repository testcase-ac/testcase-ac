#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int x = inf.readInt(1, 1000000000, "x");
    inf.readEoln();

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        int a = inf.readInt(1, 1000000, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, 10, "b_i");
        inf.readEoln();
    }

    inf.readEof();
}
