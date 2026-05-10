#include "testlib.h"
#include <cmath>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(2, 1024, "N"); // 2^1=2, 2^10=1024
    inf.readEoln();

    // 2. Check N is a power of 2
    ensuref((N & (N - 1)) == 0, "N (%d) is not a power of 2", N);

    // 3. Read N x N grid, each K in [1, 100000]
    vector<vector<int>> grid(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        grid[i] = inf.readInts(N, 1, 100000, "K");
        inf.readEoln();
    }

    inf.readEof();
}
