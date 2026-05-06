#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read sizes of sets A and B
    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln();

    // Read elements of A
    vector<int> A = inf.readInts(n, 1, 100000000, "a_i");
    inf.readEoln();

    // Read elements of B
    vector<int> B = inf.readInts(m, 1, 100000000, "b_i");
    inf.readEoln();

    // Check A for duplicates
    {
        vector<int> tmp = A;
        sort(tmp.begin(), tmp.end());
        for (int i = 1; i < (int)tmp.size(); i++) {
            ensuref(tmp[i] != tmp[i-1],
                    "Duplicate element in set A at positions %d and %d: value %d",
                    i, i+1, tmp[i]);
        }
    }

    // Check B for duplicates
    {
        vector<int> tmp = B;
        sort(tmp.begin(), tmp.end());
        for (int i = 1; i < (int)tmp.size(); i++) {
            ensuref(tmp[i] != tmp[i-1],
                    "Duplicate element in set B at positions %d and %d: value %d",
                    i, i+1, tmp[i]);
        }
    }

    inf.readEof();
    return 0;
}
