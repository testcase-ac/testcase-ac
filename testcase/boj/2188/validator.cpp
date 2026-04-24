#include "testlib.h"
#include <vector>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 200, "N");
    inf.readSpace();
    int M = inf.readInt(1, 200, "M");
    inf.readEoln();

    // For each cow, read its desired barns
    for (int i = 1; i <= N; i++) {
        // Read S_i
        char bufSi[30];
        sprintf(bufSi, "S_%d", i);
        int S = inf.readInt(0, M, bufSi);

        // Track duplicates
        vector<bool> seen(M+1, false);

        // Read the S barn indices
        for (int j = 1; j <= S; j++) {
            inf.readSpace();
            char bufBij[30];
            sprintf(bufBij, "barn_%d_%d", i, j);
            int b = inf.readInt(1, M, bufBij);
            ensuref(!seen[b],
                    "Duplicate barn %d for cow %d", b, i);
            seen[b] = true;
        }

        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
