#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // 2. Read M
    int M = inf.readInt(1, N, "M");
    inf.readEoln();

    // 3. Read M positions
    vector<int> x = inf.readInts(M, 0, N, "x_i");
    inf.readEoln();

    // 4. Check strictly increasing order and no duplicates
    for (int i = 1; i < M; ++i) {
        ensuref(x[i-1] < x[i], 
            "Lamp positions must be strictly increasing and unique: x[%d]=%d, x[%d]=%d", i-1, x[i-1], i, x[i]);
    }

    // 5. All positions are within [0, N] (already checked by readInts)

    // 6. Check for global formatting: EOF
    inf.readEof();
}
