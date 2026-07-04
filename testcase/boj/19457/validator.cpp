#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 1000000, "n");
    inf.readSpace();
    long long h = inf.readLong(0LL, 1000000000LL, "H");
    inf.readEoln();

    ensuref(n == 0 || h >= 2, "positive ledges require H >= 2, got n=%d and H=%lld", n, h);

    vector<long long> a;
    a.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        long long value = inf.readLong(1LL, h - 1, "a_i");
        if (i == 0) {
            ensuref(h > value, "expected H > a_1, got H=%lld and a_1=%lld", h, value);
        } else {
            ensuref(a.back() > value,
                    "ledge heights must be strictly decreasing: a_%d=%lld, a_%d=%lld",
                    i, a.back(), i + 1, value);
        }
        a.push_back(value);
    }
    inf.readEoln();
    inf.readEof();
}
