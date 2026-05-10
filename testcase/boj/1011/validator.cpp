#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: not specified, assume up to 100000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read x and y: 0 ≤ x < y < 2^31
        long long x = inf.readLong(0LL, 2147483647LL, "x");
        inf.readSpace();
        long long y = inf.readLong(0LL, 2147483647LL, "y");
        inf.readEoln();

        ensuref(x < y,
                "In test case %d, x must be less than y: found x=%lld, y=%lld",
                tc, x, y);
    }

    inf.readEof();
    return 0;
}
