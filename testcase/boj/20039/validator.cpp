#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(3, 500000, "n");
    inf.readEoln();

    // Read the sequence Q of length n
    vector<int> Q = inf.readInts(n, 1, 1000000000, "Q");
    inf.readEoln();

    // Check that all values are distinct
    vector<int> tmp = Q;
    sort(tmp.begin(), tmp.end());
    for (int i = 1; i < n; i++) {
        ensuref(tmp[i] != tmp[i-1],
                "Duplicate value detected: %d appears more than once", tmp[i]);
    }

    inf.readEof();
    return 0;
}
