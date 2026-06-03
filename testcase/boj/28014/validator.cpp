#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000000, "n");
    inf.readEoln();

    inf.readInts(n, 1, 1000000, "h");
    inf.readEoln();
    inf.readEof();
}
