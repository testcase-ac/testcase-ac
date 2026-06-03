#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr long long MAX_K = 1000000000000000LL;

    long long k = inf.readLong(2LL, MAX_K, "K");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        inf.readLong(1LL, k - 1, "A_i");
        if (i + 1 == q) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    inf.readEof();
}
