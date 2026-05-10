#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: odd natural number, 3 ≤ N ≤ 999
    int N = inf.readInt(3, 999, "N");
    ensuref(N % 2 == 1, "N must be odd, but got %d", N);
    inf.readEoln();

    // Read k: 1 ≤ k ≤ N^2
    long long maxK = 1LL * N * N;
    long long k = inf.readLong(1LL, maxK, "k");
    inf.readEoln();

    // No extra content
    inf.readEof();

    return 0;
}
