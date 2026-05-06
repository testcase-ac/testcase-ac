#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single line with four integers A,B,C,D in given range, canonical via readInt.
    long long A = inf.readLong(-1000000000LL, 1000000000LL, "A");
    inf.readSpace();
    long long B = inf.readLong(-1000000000LL, 1000000000LL, "B");
    inf.readSpace();
    long long C = inf.readLong(-1000000000LL, 1000000000LL, "C");
    inf.readSpace();
    long long D = inf.readLong(-1000000000LL, 1000000000LL, "D");
    inf.readEoln();

    // No extra structural/global constraints in statement beyond ranges.

    inf.readEof();
}
