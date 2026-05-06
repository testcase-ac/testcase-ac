#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of wizards / appointments
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    vector<long long> A(N), B(N);
    for (int i = 0; i < N; i++) {
        A[i] = inf.readLong(1LL, 1000000000LL, "A_i");
        inf.readSpace();
        B[i] = inf.readLong(1LL, 1000000000LL, "B_i");
        inf.readEoln();
    }

    // No additional global constraints are specified that must be enforced
    // by the validator beyond the numeric ranges and format.

    inf.readEof();
}
