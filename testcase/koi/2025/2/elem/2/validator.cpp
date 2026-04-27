#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    long long s = inf.readLong(-1000000000LL, 1000000000LL, "s");
    (void)s;
    inf.readEoln();

    long long prev = -1000000000LL;
    for (int i = 1; i <= n; ++i) {
        long long a = inf.readLong(-1000000000LL, 1000000000LL, "A_i");
        ensuref(i == 1 || prev <= a, "A_%d=%lld is smaller than A_%d=%lld", i, a, i - 1, prev);
        prev = a;
        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
