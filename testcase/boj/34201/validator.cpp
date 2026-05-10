#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and s
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int s = inf.readInt(-1000000000, 1000000000, "s");
    inf.readEoln();

    // Read A_1 ... A_N
    vector<int> A = inf.readInts(N, -1000000000, 1000000000, "A_i");
    inf.readEoln();

    // Check non-decreasing order
    for (int i = 1; i < N; ++i) {
        ensuref(A[i-1] <= A[i], "A[%d]=%d > A[%d]=%d: Mirror positions must be non-decreasing", i, A[i-1], i+1, A[i]);
    }

    inf.readEof();
}
