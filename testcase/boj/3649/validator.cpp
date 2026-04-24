#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    // Read until EOF: each test case consists of x, n, and n lines of lengths.
    while (!inf.eof()) {
        setTestCase(++tc);
        ensuref(tc <= 100000,
                "Number of test cases exceeds limit: %d > 100000", tc);

        // Read x: hole width in cm, 1 ≤ x ≤ 20
        int x = inf.readInt(1, 20, "x");
        inf.readEoln();

        // Read n: number of lego pieces, 0 ≤ n ≤ 1e6
        int n = inf.readInt(0, 1000000, "n");
        inf.readEoln();

        // Read each lego piece length ℓ: 1 ≤ ℓ ≤ 1e8 (nanometers)
        for (int i = 0; i < n; i++) {
            long long l = inf.readLong(1LL, 100000000LL, "l");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
