#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Read A[0..N-1]
    vector<int> A = inf.readInts(N, 1, 1000000, "A_i");
    inf.readEoln();

    // Check all elements are distinct
    set<int> seen;
    for (int i = 0; i < N; ++i) {
        ensuref(seen.insert(A[i]).second, "A[%d]=%d is duplicated", i+1, A[i]);
    }

    // Read S
    int S = inf.readInt(0, 1000000, "S");
    inf.readEoln();

    inf.readEof();
}
