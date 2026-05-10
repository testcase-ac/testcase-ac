#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and K
    int N = inf.readInt(1, 500, "N");
    inf.readSpace();
    int K = inf.readInt(1, 1000000000, "K");
    inf.readEoln();

    // 2. Read A_1 ... A_N
    vector<int> A = inf.readInts(N, 1, N, "A_i");
    inf.readEoln();

    // 3. Check that all A_i are unique (no duplicates)
    set<int> seen;
    for (int i = 0; i < N; ++i) {
        ensuref(seen.insert(A[i]).second, "Duplicate value %d found at position %d", A[i], i+1);
    }

    inf.readEof();
}
