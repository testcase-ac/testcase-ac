#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 1;
    const int N_MAX = 500000;

    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readEoln();

    string S = inf.readToken("[WB]+", "S");
    inf.readEoln();

    ensuref((int)S.size() == N,
            "Length of S must be exactly N (%d), but got %d",
            N, (int)S.size());

    inf.readEof();
}
