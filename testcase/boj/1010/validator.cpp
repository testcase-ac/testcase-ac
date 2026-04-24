#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases, assume up to 100000 if unspecified
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N and M: 0 < N <= M < 30
        int N = inf.readInt(1, 29, "N");
        inf.readSpace();
        int M = inf.readInt(1, 29, "M");
        inf.readEoln();

        ensuref(N <= M,
                "In test case %d, N must be <= M, but N=%d, M=%d",
                tc, N, M);
    }

    inf.readEof();
    return 0;
}
