#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int kMaxN = 200000;
    constexpr long long kModMinusOne = 998244352LL;

    int n = inf.readInt(2, kMaxN, "n");
    inf.readEoln();

    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        long long a = inf.readLong(1LL, kModMinusOne, "a_i");
        sum += a;
        ensuref(sum <= kModMinusOne,
                "sum of a_i exceeds 998244352 after index %d", i);

        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    ensuref(sum >= n, "sum of a_i must be at least n, got %lld", sum);
    inf.readEof();
}
