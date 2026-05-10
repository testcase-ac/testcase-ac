#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of polygons
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read A_i: number of vertices of each polygon
    vector<int> A = inf.readInts(N, 3, 100, "A_i");
    inf.readEoln();

    // Check non-increasing constraint: A_i >= A_{i+1}
    for (int i = 0; i + 1 < N; ++i) {
        ensuref(A[i] >= A[i + 1],
                "Sequence A must be non-increasing: A[%d]=%d < A[%d]=%d",
                i + 1, A[i], i + 2, A[i + 1]);
    }

    inf.readEof();
}
