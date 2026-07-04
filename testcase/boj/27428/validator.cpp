#include "testlib.h"

#include <algorithm>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long maxN = 1000000000000LL;
    const int maxD = 1000000;

    long long n = inf.readLong(3LL, maxN, "N");
    inf.readEoln();

    int k = inf.readInt(1, 22, "K");
    inf.readEoln();

    for (int i = 0; i < k; ++i) {
        if (i > 0) {
            inf.readSpace();
        }

        // CHECK: The prose states 2 <= d_i <= N, while the limit block says 1 <= d_i.
        // Enforce the stricter lower bound from the input description.
        int d = inf.readInt(2, static_cast<int>(std::min<long long>(n, maxD)), "d_i");
        (void)d;
    }
    inf.readEoln();

    inf.readEof();
}
