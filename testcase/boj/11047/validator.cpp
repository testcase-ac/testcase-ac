#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 10, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100000000, "K");
    inf.readEoln();

    // Read coin values A_i
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = inf.readInt(1, 1000000, "A_i");
        inf.readEoln();
    }

    // Check global properties
    ensuref(A[0] == 1,
            "A[1] must be 1, found %d", A[0]);
    for (int i = 1; i < N; i++) {
        ensuref(A[i] >= A[i-1],
                "A[%d]=%d is smaller than A[%d]=%d", i+1, A[i], i, A[i-1]);
        ensuref(A[i] % A[i-1] == 0,
                "A[%d]=%d is not a multiple of A[%d]=%d", i+1, A[i], i, A[i-1]);
    }

    inf.readEof();
    return 0;
}
