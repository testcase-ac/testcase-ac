#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of disks, 1 ≤ N ≤ 60
    int N = inf.readInt(1, 60, "N");
    inf.readSpace();

    // The total number of moves in the minimal solution is 2^N - 1.
    // Compute that as unsigned long long to avoid signed overflow,
    // then cast to long long (it fits since N ≤ 60).
    unsigned long long maxMoves = (1ULL << N) - 1;
    long long maxK = (long long)maxMoves;

    // Read K: 1 ≤ K ≤ 2^N - 1
    long long K = inf.readLong(1LL, maxK, "K");
    inf.readEoln();

    inf.readEof();
    return 0;
}
