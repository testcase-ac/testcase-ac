#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    // This is an input validator: it validates the problem's *input*, not any solution output.
    registerValidation(argc, argv);

    // One test case, single line: n a b
    int n = inf.readInt(2, 500, "n");
    inf.readSpace();
    int a = inf.readInt(1, n, "a");
    inf.readSpace();
    int b = inf.readInt(1, n, "b");
    inf.readEoln();

    // No further input
    inf.readEof();
}
