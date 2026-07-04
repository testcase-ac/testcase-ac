#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long kMinTemp = -1000000000LL;
    const long long kMaxTemp = 1000000000LL;

    int q = inf.readInt(1, 500, "q");
    inf.readEoln();

    for (int tc = 1; tc <= q; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100, "n");
        inf.readSpace();
        inf.readLong(kMinTemp, kMaxTemp, "m");
        inf.readEoln();

        long long previousTime = 0;
        for (int i = 1; i <= n; ++i) {
            long long t = inf.readLong(1LL, 1000000000LL, "t_i");
            inf.readSpace();
            long long l = inf.readLong(kMinTemp, kMaxTemp, "l_i");
            inf.readSpace();
            long long h = inf.readLong(l, kMaxTemp, "h_i");
            inf.readEoln();

            ensuref(previousTime <= t,
                    "visit times must be non-decreasing: t_%d=%lld, previous=%lld",
                    i, t, previousTime);
            previousTime = t;
        }
    }

    inf.readEof();
    return 0;
}
