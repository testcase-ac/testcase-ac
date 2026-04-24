#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000000000, "M");
    inf.readEoln();
    // Check N < M
    ensuref(N < M, "Constraint violation: N (%d) must be less than M (%d)", N, M);

    vector<int> P(N);
    for (int i = 0; i < N; i++) {
        P[i] = inf.readInt(1, M-1, "P_i");
        inf.readSpace();
        // C_i is not used for further validation beyond bounds
        inf.readInt(1, 1000000000, "C_i");
        inf.readEoln();
    }

    // Ensure all P_i are distinct
    vector<int> sortedP = P;
    sort(sortedP.begin(), sortedP.end());
    for (int i = 1; i < N; i++) {
        ensuref(sortedP[i] != sortedP[i-1],
                "Duplicate sensor position detected: %d", sortedP[i]);
    }

    inf.readEof();
    return 0;
}
