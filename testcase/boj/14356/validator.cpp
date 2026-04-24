#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 75, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Read N, R, P, S
        int N = inf.readInt(1, 12, "N");
        inf.readSpace();
        int R = inf.readInt(0, (1 << N), "R");
        inf.readSpace();
        int P = inf.readInt(0, (1 << N), "P");
        inf.readSpace();
        int S = inf.readInt(0, (1 << N), "S");
        inf.readEoln();

        // Check that R + P + S == 2^N
        long long total = (long long)R + P + S;
        long long expected = 1LL << N;
        ensuref(total == expected,
                "Test case %d: R+P+S must equal 2^N, but got %d+%d+%d = %lld (expected %lld)",
                tc, R, P, S, total, expected);
    }

    inf.readEof();
    return 0;
}
