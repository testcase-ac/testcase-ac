#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read W, L, N
    long long W = inf.readLong(1LL, 100000000LL, "W");
    inf.readSpace();
    int L = inf.readInt(1, 1000, "L");
    inf.readSpace();
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // For each lock, read top and bottom sequences
    for (int k = 0; k < N; ++k) {
        // top sequence: L integers in [0, W-1]
        vector<int> top = inf.readInts(L, 0, W - 1, "top");
        inf.readEoln();

        // bottom sequence: L integers in [0, W-1]
        vector<int> bottom = inf.readInts(L, 0, W - 1, "bottom");
        inf.readEoln();

        // Check that at each position there is at least 1 cm empty space:
        // top[i] + bottom[i] <= W-1
        for (int i = 0; i < L; ++i) {
            long long sum = (long long)top[i] + (long long)bottom[i];
            ensuref(sum <= W - 1,
                    "Lock %d, position %d: top+bottom = %d which is >= W=%lld (no empty space)",
                    k + 1, i + 1, (int)sum, W);
        }
    }

    inf.readEof();
    return 0;
}
