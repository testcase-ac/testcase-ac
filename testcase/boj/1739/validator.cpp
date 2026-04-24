#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N, M, K
        int N = inf.readInt(1, 1000, "N");
        inf.readSpace();
        int M = inf.readInt(1, 1000, "M");
        inf.readSpace();
        int K = inf.readInt(1, 1000, "K");
        inf.readEoln();

        // Read bus routes
        for (int i = 1; i <= K; i++) {
            char buf[50];
            // A: row of start
            sprintf(buf, "bus[%d].A[%d]", tc, i);
            int A = inf.readInt(1, N, buf);
            inf.readSpace();
            // B: column of start
            sprintf(buf, "bus[%d].B[%d]", tc, i);
            int B = inf.readInt(1, M, buf);
            inf.readSpace();
            // C: row of end
            sprintf(buf, "bus[%d].C[%d]", tc, i);
            int C = inf.readInt(1, N, buf);
            inf.readSpace();
            // D: column of end
            sprintf(buf, "bus[%d].D[%d]", tc, i);
            int D = inf.readInt(1, M, buf);
            inf.readEoln();
            // No further validation: start and end may coincide
        }
    }

    inf.readEof();
    return 0;
}
