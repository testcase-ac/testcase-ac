#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Read the sequence of n distinct positive integers
    vector<int> a = inf.readInts(n, 1, 1000000, "a_i");
    inf.readEoln();

    // Check distinctness
    {
        vector<int> b = a;
        sort(b.begin(), b.end());
        for (int i = 1; i < n; i++) {
            ensuref(b[i] != b[i-1],
                    "Duplicate value %d found in the sequence", b[i]);
        }
    }

    // Read x
    inf.readInt(1, 2000000, "x");
    inf.readEoln();

    // No extra characters
    inf.readEof();
    return 0;
}
