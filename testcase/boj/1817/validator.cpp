#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N, M
    int N = inf.readInt(0, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M"); // natural number <= 1000
    inf.readEoln();

    if (N > 0) {
        // Second line: N book weights
        vector<int> w = inf.readInts(N, 1, M, "w_i");
        inf.readEoln();

        // The problem guarantees that the minimal number of boxes answer always exists.
        // That is trivially satisfied because each w_i <= M, so we don't need extra checks
        // beyond the per-weight bound already enforced. No need to simulate boxing here,
        // since there is no further global invariant stated about the packing process.
    }

    inf.readEof();
}
