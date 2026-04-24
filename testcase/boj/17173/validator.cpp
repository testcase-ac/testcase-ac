#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, N - 1, "M");
    inf.readEoln();

    // Read the K_i array
    vector<int> K = inf.readInts(M, 2, 1000, "K");
    inf.readEoln();

    // Check that K is strictly increasing (distinct and sorted ascending)
    for (int i = 1; i < M; i++) {
        ensuref(K[i-1] < K[i],
                "K must be strictly increasing, but K[%d]=%d >= K[%d]=%d",
                i-1, K[i-1], i, K[i]);
    }

    // End of file
    inf.readEof();
    return 0;
}
