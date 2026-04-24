#include "testlib.h"
#include <vector>
using namespace std;

static bool isPowerOfTwo(int x) {
    return x > 0 && (x & (x - 1)) == 0;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // Read n
        int n = inf.readInt(1, 1000, "n");
        inf.readEoln();

        // Read the sequence of block lengths
        vector<int> a = inf.readInts(n, 1, 8192, "length");
        inf.readEoln();

        // Check each is a power of two, and sum constraint
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            int v = a[i];
            ensuref(isPowerOfTwo(v),
                    "length[%d] in test case %d is not a power of two: %d",
                    i + 1, tc + 1, v);
            sum += v;
        }
        ensuref(sum <= (1 << 13),
                "Sum of lengths in test case %d exceeds 2^13: %lld",
                tc + 1, sum);
    }

    inf.readEof();
    return 0;
}
