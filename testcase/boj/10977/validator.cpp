#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no T bound; use the local default cap.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int m = inf.readInt(1, 1000000, "M");
        inf.readSpace();
        int n = inf.readInt(1, m, "N");
        inf.readEoln();

        totalN += n;
        // CHECK: T is unbounded in the statement; cap total listed foods to keep
        // primarily numeric inputs below the local practical token-volume limit.
        ensuref(totalN <= 4700000LL, "sum of N is too large: %lld", totalN);

        int previous = 0;
        for (int i = 1; i <= n; ++i) {
            int x = inf.readInt(1, m, "x_i");
            inf.readEoln();
            ensuref(previous < x, "x_i values must be strictly increasing at index %d", i);
            previous = x;
        }
    }

    inf.readEof();
}
