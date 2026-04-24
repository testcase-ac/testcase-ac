#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read M, N, L, G
        int M = inf.readInt(2, 100, "M");
        inf.readSpace();
        int N = inf.readInt(2, 100, "N");
        inf.readSpace();
        int L = inf.readInt(1, 10, "L");
        inf.readSpace();
        int G = inf.readInt(1, 1000000, "G");
        inf.readEoln();

        // Read M rows of horizontal costs (each has N-1 values)
        for (int i = 0; i < M; i++) {
            inf.readInts(N - 1, 1, 1000, "h");
            inf.readEoln();
        }

        // Read M-1 rows of vertical costs (each has N values)
        for (int i = 0; i < M - 1; i++) {
            inf.readInts(N, 1, 1000, "v");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
