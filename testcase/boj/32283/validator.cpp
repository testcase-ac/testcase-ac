#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: length of the binary string
    int N = inf.readInt(1, 10, "N");
    inf.readEoln();

    // S: binary string of length N, can start with 0
    string S = inf.readToken("[01]+", "S");
    inf.readEoln();

    ensuref((int)S.size() == N,
            "Length of S (%d) must be equal to N (%d)", (int)S.size(), N);

    inf.readEof();
}
