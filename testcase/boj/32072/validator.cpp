#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 300000, "N");
    inf.readEoln();

    // Read parent array P_2 ... P_N
    vector<int> P(N+1);
    for (int i = 2; i <= N; i++) {
        // Each P_i must satisfy 1 <= P_i < i
        P[i] = inf.readInt(1, i-1, "P_i");
        if (i < N) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    // Read weights A_1 ... A_N
    vector<int> A = inf.readInts(N, 1, N, "A_i");
    inf.readEoln();

    // Check that A is a permutation (all distinct)
    vector<char> seen(N+1, 0);
    for (int i = 0; i < N; i++) {
        int x = A[i];
        ensuref(!seen[x], "Duplicate weight A_i = %d", x);
        seen[x] = 1;
    }

    inf.readEof();
    return 0;
}
