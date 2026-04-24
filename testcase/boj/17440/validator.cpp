#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of tournaments
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Each tournament has a rating interval [A_i, B_i]
    for (int i = 0; i < N; i++) {
        int A = inf.readInt(1, 9999999, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, 9999999, "B_i");
        inf.readEoln();

        ensuref(A <= B,
                "For line %d: A_i must be <= B_i, but got A_i=%d, B_i=%d",
                i+1, A, B);
    }

    inf.readEof();
    return 0;
}
