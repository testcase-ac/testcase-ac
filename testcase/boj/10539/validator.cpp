#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read sequence B of length N
    vector<long long> B = inf.readLongs(N, 1LL, 1000000000LL, "B");
    inf.readEoln();

    // Validate that B indeed comes from some positive A sequence
    // where A_i = i*B_i - sum_{j=1..i-1} A_j, and 1 <= A_i <= 1e9
    long long prev_sum = 0;  // sum of A[1..i-1]
    for (int i = 1; i <= N; i++) {
        // sum up to i should be exactly B[i-1] * i
        long long sum_i = B[i-1] * (long long)i;
        long long Ai = sum_i - prev_sum;
        ensuref(Ai >= 1 && Ai <= 1000000000LL,
                "Invalid A_%d = %lld derived from B_%d = %lld; must satisfy 1 <= A_i <= 1e9",
                i, Ai, i, B[i-1]);
        prev_sum = sum_i;
    }

    inf.readEof();
    return 0;
}
