#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    int totalCells = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 100, "N");
        inf.readSpace();
        int K = inf.readInt(1, 25, "K");
        inf.readEoln();

        totalCells += N * K;
        // CHECK: The statement omits an upper bound for T; cap total matrix size at one largest case.
        ensuref(totalCells <= 100 * 25, "sum of N*K over all test cases must not exceed 2500");

        for (int i = 0; i < N; ++i) {
            inf.readInts(K, 0, 1000000, "P_ij");
            inf.readEoln();
        }
    }

    inf.readEof();
}
