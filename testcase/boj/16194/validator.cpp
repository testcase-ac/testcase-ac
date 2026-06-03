#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    inf.readInts(n, 1, 10000, "P_i");
    inf.readEoln();
    inf.readEof();
}
