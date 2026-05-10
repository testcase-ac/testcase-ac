#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read array A of size N
    vector<int> A = inf.readInts(N, 1, 1000000, "A_i");
    inf.readEoln();

    // Ensure all A_i are distinct
    set<int> seen;
    for (int i = 0; i < N; i++) {
        auto res = seen.insert(A[i]);
        ensuref(res.second,
                "Duplicate element at position %d: %d", 
                i + 1, A[i]);
    }

    inf.readEof();
    return 0;
}
