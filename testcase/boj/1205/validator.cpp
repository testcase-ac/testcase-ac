#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, newScore, P
    // N: 0 <= N <= 50 (we'll further ensure N <= P)
    int N = inf.readInt(0, 50, "N");
    inf.readSpace();
    int newScore = inf.readInt(0, 2000000000, "newScore");
    inf.readSpace();
    int P = inf.readInt(10, 50, "P");
    inf.readEoln();

    // Global constraint: N <= P
    ensuref(N <= P, "N (%d) must be <= P (%d)", N, P);

    // If N > 0, read the ranking list
    if (N > 0) {
        vector<int> scores = inf.readInts(N, 0, 2000000000, "score");
        inf.readEoln();
        // Check non-increasing order
        for (int i = 0; i + 1 < N; i++) {
            ensuref(scores[i] >= scores[i+1],
                    "Ranking list not non-increasing at index %d: %d < %d",
                    i, scores[i], scores[i+1]);
        }
    }

    inf.readEof();
    return 0;
}
