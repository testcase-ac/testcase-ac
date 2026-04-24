#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 1000, "K");
    inf.readEoln();

    // Check that it's possible to place K dominoes on an N x 3 grid.
    // The maximum number of dominoes that can fit is floor((3*N)/2).
    long long max_dominoes = (3LL * N) / 2;
    ensuref((long long)K <= max_dominoes,
            "Too many dominoes: K = %d, but maximum possible for N = %d is %lld",
            K, N, max_dominoes);

    // Read the board values: N rows, 3 columns each, |value| < 1e6
    for (int i = 0; i < N; i++) {
        // Read 3 integers in [-999999, 999999]
        vector<int> row = inf.readInts(3, -999999, 999999,
                                       ("cell_row" + to_string(i)).c_str());
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
