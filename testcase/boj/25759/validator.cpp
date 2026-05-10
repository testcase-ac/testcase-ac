#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of flowers
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // A_i: beauty values
    vector<int> A = inf.readInts(N, 1, 100, "A_i");
    inf.readEoln();

    // No further global properties are specified in the statement:
    // - No constraints on subsequence selection.
    // - No guarantee about existence of non-empty bouquet beyond N >= 2.
    // Therefore, no additional simulation or structural checks are needed.

    inf.readEof();
}
