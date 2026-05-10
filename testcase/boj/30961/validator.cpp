#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read array A of size N, each in [0, 1e9]
    vector<int> A = inf.readInts(N, 0, 1000000000, "A_i");
    inf.readEoln();

    // No extra global constraints given by the problem besides ranges.
    // No need to simulate or check answer existence: any array is valid.

    inf.readEof();
}
