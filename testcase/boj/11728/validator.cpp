#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read sizes of the two arrays
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000000, "M");
    inf.readEoln();

    // Read array A
    vector<long long> A = inf.readLongs(N, -1000000000LL, 1000000000LL, "A_i");
    inf.readEoln();

    // Read array B
    vector<long long> B = inf.readLongs(M, -1000000000LL, 1000000000LL, "B_i");
    inf.readEoln();

    // Validate that A is non-decreasing
    for (int i = 1; i < N; i++) {
        ensuref(A[i-1] <= A[i],
                "Array A not sorted at positions %d and %d: %lld > %lld",
                i-1, i, A[i-1], A[i]);
    }
    // Validate that B is non-decreasing
    for (int i = 1; i < M; i++) {
        ensuref(B[i-1] <= B[i],
                "Array B not sorted at positions %d and %d: %lld > %lld",
                i-1, i, B[i-1], B[i]);
    }

    // End of file
    inf.readEof();
    return 0;
}
