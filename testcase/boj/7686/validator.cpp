#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCase = 1;
    while (true) {
        int n = inf.readInt(0, 1000, "n");
        inf.readSpace();
        int k = inf.readInt(0, 999, "k");
        inf.readEoln();

        if (n == 0) {
            ensuref(k == 0, "only the terminating case may have n = 0");
            break;
        }

        setTestCase(testCase);
        ensuref(k < n, "k must be less than n, got n = %d and k = %d", n, k);

        vector<long long> a(n);
        vector<long long> b(n);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            a[i] = inf.readLong(0LL, 1000000000LL, "a_i");
        }
        inf.readEoln();

        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            b[i] = inf.readLong(1LL, 1000000000LL, "b_i");
            ensuref(a[i] <= b[i],
                    "a_%d must not exceed b_%d, got %lld > %lld",
                    i + 1,
                    i + 1,
                    a[i],
                    b[i]);
        }
        inf.readEoln();

        ++testCase;
    }

    inf.readEof();
    return 0;
}
