#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: T and M
    // Statement: 1 ≤ T ≤ 1000 (and global rule allows up to 100000)
    int T = inf.readInt(1, 1000, "T");
    inf.readSpace();
    // From subtasks and problem: 2 ≤ M ≤ 1_000_000
    int M = inf.readInt(2, 1000000, "M");
    inf.readEoln();

    long long totalN = 0;

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // Each of the following T lines:
        // N followed by N positive integers x_i
        int N = inf.readInt(1, 1000000, "N");
        totalN += N;
        ensuref(totalN <= 1000000,
                "Sum of all N over test cases exceeds 1_000_000 (now %lld)", totalN);

        // There will be exactly one space separating consecutive numbers
        for (int i = 0; i < N; ++i) {
            inf.readSpace();
            int x = inf.readInt(1, 1000000, "x_i");
            (void)x;
        }
        inf.readEoln();
    }

    inf.readEof();
}
