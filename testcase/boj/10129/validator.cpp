#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of trees
    int n = inf.readInt(2, 1000000, "n");
    inf.readEoln();

    // Read tree heights
    vector<int> d = inf.readInts(n, 1, 1000000000, "d_i");
    inf.readEoln();

    // Read number of queries (birds)
    int q = inf.readInt(1, 25, "q");
    inf.readEoln();

    // Each k_i must be between 1 and n-1
    for (int i = 0; i < q; i++) {
        int k = inf.readInt(1, n - 1, "k_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
