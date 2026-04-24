#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 11, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; tc++) {
        setTestCase(tc+1);

        // Read N and M
        int N = inf.readInt(1, 100000, "N");
        inf.readSpace();
        int M = inf.readInt(1, 100000, "M");
        inf.readEoln();

        // Read M directed edges
        for (int i = 0; i < M; i++) {
            // Read A_i
            char bufA[32];
            sprintf(bufA, "A_%d", i);
            int A = inf.readInt(0, N-1, bufA);
            inf.readSpace();
            // Read B_i
            char bufB[32];
            sprintf(bufB, "B_%d", i);
            int B = inf.readInt(0, N-1, bufB);
            inf.readEoln();
            // Loops (A == B) are allowed per problem statement
        }

        // Between test cases there must be exactly one blank line
        if (tc < T-1) {
            inf.readEoln(); // blank line
        }
    }

    inf.readEof();
    return 0;
}
