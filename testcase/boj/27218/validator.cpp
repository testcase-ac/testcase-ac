#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single-test input: two integers n and k on one line.
    long long n = inf.readLong(2LL, 200000LL, "n");
    inf.readSpace();
    int k = inf.readInt(2, 30, "k");
    inf.readEoln();
    inf.readEof();

    // Nothing else to validate on the input side.

    return 0;
}
