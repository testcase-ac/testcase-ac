#include "testlib.h"
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and ensure it's even and in [4,20]
    int N = inf.readInt(4, 20, "N");
    ensuref(N % 2 == 0, "N must be even, got %d", N);
    inf.readEoln();

    // Read the S matrix: N lines of N integers each
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            // Read S[i][j] in [0,100]
            char nameBuf[32];
            sprintf(nameBuf, "S_%d_%d", i, j);
            int sij = inf.readInt(0, 100, nameBuf);
            // On the same line, spaces between numbers except after last
            if (j < N) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
            // Enforce S_ii == 0, and S_ij >= 1 for i != j
            if (i == j) {
                ensuref(sij == 0, "S_%d_%d must be 0 (diagonal), got %d", i, j, sij);
            } else {
                ensuref(sij >= 1, "S_%d_%d must be >= 1 for i!=j, got %d", i, j, sij);
            }
        }
    }

    // No extra content
    inf.readEof();
    return 0;
}
