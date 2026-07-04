#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    int totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 200000, "n");
        inf.readEoln();
        totalN += n;
        ensuref(totalN <= 200000, "sum of n exceeds 200000 after test case %d", tc);

        vector<int> a = inf.readInts(n, 1, n, "a_i");
        inf.readEoln();

        for (int i = 1; i < n; ++i) {
            ensuref(a[i - 1] != a[i],
                    "adjacent equal values at test case %d, positions %d and %d: %d",
                    tc, i, i + 1, a[i]);
        }
    }

    inf.readEof();
}
