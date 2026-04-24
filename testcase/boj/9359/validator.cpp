#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    // Read each test case
    for (int tc = 1; tc <= T; tc++) {
        long long A = inf.readLong(1LL, 1000000000000000LL, "A");
        inf.readSpace();
        long long B = inf.readLong(1LL, 1000000000000000LL, "B");
        inf.readSpace();
        int N = inf.readInt(1, 1000000000, "N");
        inf.readEoln();

        // Validate that A ≤ B
        ensuref(A <= B,
                "In test case %d, A must be ≤ B but got A=%lld, B=%lld",
                tc, A, B);
    }

    inf.readEof();
    return 0;
}
