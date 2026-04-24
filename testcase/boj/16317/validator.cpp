#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of dirty pushes
    int n = inf.readInt(1, 365, "n");
    inf.readEoln();

    // Read the days of dirty pushes
    vector<int> d = inf.readInts(n, 1, 365, "d_i");
    inf.readEoln();

    // Check that the days are strictly increasing
    for (int i = 1; i < n; i++) {
        ensuref(d[i] > d[i-1],
                "d_i not strictly increasing at positions %d and %d: %d >= %d",
                i-1, i, d[i-1], d[i]);
    }

    inf.readEof();
    return 0;
}
