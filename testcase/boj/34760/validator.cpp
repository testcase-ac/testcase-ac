#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N = 15;
    // Read exactly 15 integers on a single line.
    vector<long long> A(N);
    for (int i = 0; i < N; ++i) {
        A[i] = inf.readLong(1LL, 1000000000LL, "A_i");
        if (i + 1 < N) inf.readSpace();
    }
    inf.readEoln();

    // No additional global constraints guaranteed in statement
    // (such as existence of an answer), so nothing more to check.

    inf.readEof();
}
