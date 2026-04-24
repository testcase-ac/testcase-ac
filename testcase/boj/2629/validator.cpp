#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of weights
    int N = inf.readInt(1, 30, "N");
    inf.readEoln();

    // Weights array, non-decreasing order, each between 1 and 500
    vector<int> w = inf.readInts(N, 1, 500, "weight_i");
    for (int i = 1; i < N; i++) {
        ensuref(w[i] >= w[i-1],
                "Weights must be non-decreasing: weight_%d = %d < weight_%d = %d",
                i+1, w[i], i, w[i-1]);
    }
    inf.readEoln();

    // Number of marbles
    int M = inf.readInt(1, 7, "M");
    inf.readEoln();

    // Marble weights, each between 1 and 40000
    vector<int> m = inf.readInts(M, 1, 40000, "marble_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
