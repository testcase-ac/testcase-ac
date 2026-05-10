#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: M (number of colors)
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    // Second line: M integers, a_i (number of stones of color i)
    vector<int> a = inf.readInts(M, 1, 50, "a_i");
    inf.readEoln();

    // Compute N = total number of stones
    int N = 0;
    for (int i = 0; i < M; ++i) {
        N += a[i];
    }
    // N >= M (since each a_i >= 1), N <= 50*M = 2500

    // Third line: K (number of stones to pick)
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // No further input
    inf.readEof();
}
