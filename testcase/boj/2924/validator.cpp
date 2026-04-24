#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate the first line: N, A, B, C, D
    int N = inf.readInt(1, 500000, "N");
    inf.readSpace();
    long long A = inf.readLong(1LL, 1000000000000LL, "A");
    inf.readSpace();
    long long B = inf.readLong(1LL, 1000000000000LL, "B");
    inf.readSpace();
    int C = inf.readInt(0, N, "C");
    inf.readSpace();
    int D = inf.readInt(0, N, "D");
    inf.readEoln();

    // Check implied constraints
    ensuref(A <= B,
            "Constraint violation: A (%lld) must be <= B (%lld)", A, B);
    ensuref((long long)C + D < N,
            "Constraint violation: C + D = %lld must be < N = %d",
            (long long)C + D, N);

    // Read and validate the permutation line
    vector<char> seen(N+1, 0);
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(1, N, "P_i");
        if (i + 1 < N) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
        ensuref(!seen[x],
                "Duplicate detected: value %d appears more than once", x);
        seen[x] = 1;
    }

    // No extra content
    inf.readEof();
    return 0;
}
