#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(3, 200000, "N");
    inf.readEoln();

    // Read the sequence A of length N
    inf.readInts(N, -1000, 1000, "A");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
