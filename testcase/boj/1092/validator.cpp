#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    inf.readInts(n, 1, 1000000, "crane_limit");
    inf.readEoln();

    int m = inf.readInt(1, 10000, "M");
    inf.readEoln();

    inf.readInts(m, 1, 1000000, "box_weight");
    inf.readEoln();

    inf.readEof();
}
