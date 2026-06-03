#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    inf.readInt(1, 1000000, "X");
    inf.readEoln();

    inf.readInts(n, 1, 1000, "A_i");
    inf.readEoln();
    inf.readEof();
}
