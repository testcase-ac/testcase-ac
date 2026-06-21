#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50000, "T");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "N");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= 1000000, "sum of N exceeds 1000000");

        vector<int> a = inf.readInts(n, -1000000, 1000000, "a_i");
        inf.readEoln();

        for (int i = 1; i < n; ++i) {
            ensuref(a[i - 1] < a[i],
                    "a_i must be strictly increasing: a[%d]=%d, a[%d]=%d",
                    i, a[i - 1], i + 1, a[i]);
        }
    }

    inf.readEof();
}
