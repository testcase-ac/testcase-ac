#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100000;
    const long long ABS_X_LIMIT = 1000000000LL;
    const long long A_MIN = 1LL;
    const long long A_MAX = 1000000000LL;

    int N = inf.readInt(1, MAX_N, "N");
    inf.readEoln();

    vector<long long> X(N), A(N);
    long long totalPeople = 0;

    for (int i = 0; i < N; ++i) {
        X[i] = inf.readLong(-ABS_X_LIMIT, ABS_X_LIMIT, "X_i");
        inf.readSpace();
        A[i] = inf.readLong(A_MIN, A_MAX, "A_i");
        inf.readEoln();

        // sum of A[i] can go up to 1e5 * 1e9 = 1e14, fits in signed 64-bit
        totalPeople += A[i];
        ensuref(totalPeople > 0, "Total number of people overflow or became non-positive");
    }

    // No additional structural/global constraints in the statement:
    // positions need not be sorted, duplicates allowed, no requirement to check optimality.
    // We only ensured ranges and canonical integer format via readLong.

    inf.readEof();
}
