#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: 1 ≤ T ≤ 100000 (default if not specified)
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N and K: 1 ≤ N ≤ 10000, 1 ≤ K ≤ N
        int N = inf.readInt(1, 10000, "N");
        inf.readChar(' ');
        int K = inf.readInt(1, N, "K");
        inf.readEoln();

        // Read N lines, each with 5 integers in [0,10000]
        for (int i = 0; i < N; i++) {
            // Read exactly 5 scores for equipment i
            inf.readInts(5, 0, 10000, "r_i");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
