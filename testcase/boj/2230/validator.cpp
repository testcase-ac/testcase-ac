#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    long long M = inf.readLong(0LL, 2000000000LL, "M");
    inf.readEoln();

    // Read the sequence A
    vector<long long> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = inf.readLong(-1000000000LL, 1000000000LL, "A_i");
        inf.readEoln();
    }

    // Check the global guarantee: there must exist two numbers
    // whose absolute difference is >= M.
    // For absolute difference, the maximum possible is max(A) - min(A).
    long long mn = *min_element(A.begin(), A.end());
    long long mx = *max_element(A.begin(), A.end());
    long long maxDiff = mx - mn;
    ensuref(maxDiff >= M,
            "No pair has |difference| >= M: max(A)-min(A) = %lld < M = %lld",
            maxDiff, M);

    inf.readEof();
    return 0;
}
