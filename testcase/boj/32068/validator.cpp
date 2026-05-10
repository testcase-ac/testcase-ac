#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    // Validate each test case
    for (int tc = 0; tc < T; tc++) {
        // Read L, R, S
        int L = inf.readInt(-100000000, 100000000, "L");
        inf.readSpace();
        int R = inf.readInt(-100000000, 100000000, "R");
        inf.readSpace();
        int S = inf.readInt(-100000000, 100000000, "S");
        inf.readEoln();

        // Validate ordering L < S < R
        ensuref(L < S && S < R,
                "Case %d: require L < S < R, but got L=%d, S=%d, R=%d",
                tc + 1, L, S, R);
    }

    inf.readEof();
    return 0;
}
