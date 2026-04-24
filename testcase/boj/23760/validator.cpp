#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, N, "M");
    inf.readEoln();

    // Read c_i: gifts in each box
    vector<int> c = inf.readInts(N, 1, 100000, "c_i");
    inf.readEoln();

    // Read w_i: desired gifts per child
    vector<int> w = inf.readInts(M, 1, 100000, "w_i");
    inf.readEoln();

    // Read b_i: the b_i-th largest box each child picks
    vector<int> b = inf.readInts(M, 1, N, "b_i");
    inf.readEoln();

    // No further input
    inf.readEof();
    return 0;
}
