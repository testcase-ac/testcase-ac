#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000LL, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "M");
    inf.readSpace();
    int k = inf.readInt(1, 200000, "K");
    inf.readEoln();

    vector<long long> x(m);
    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        x[i] = inf.readLong(1LL, 1000000000LL, "x_i");
        if (i > 0) {
            ensuref(x[i - 1] < x[i],
                    "x_i must be strictly increasing: x_%d=%lld, x_%d=%lld",
                    i, x[i - 1], i + 1, x[i]);
        }
    }
    inf.readEoln();

    inf.readEof();
}
