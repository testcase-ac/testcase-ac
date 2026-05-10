#include "testlib.h"
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // 2. Read A_1 ... A_N
    vector<int> A = inf.readInts(N, -100000000, 100000000, "A_i");
    inf.readEoln();

    // 3. Check strictly non-decreasing order (A_i-1 <= A_i)
    for (int i = 1; i < N; ++i) {
        ensuref(A[i-1] <= A[i], "A[%d]=%d > A[%d]=%d: sequence must be non-decreasing", i-1, A[i-1], i, A[i]);
    }

    // 4. No further global properties to check (no uniqueness, no duplicates forbidden, etc.)

    // 5. End of file
    inf.readEof();
}
