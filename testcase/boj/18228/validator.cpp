#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 200000, "N");
    inf.readEoln();

    int penguin_index = -1;
    for (int i = 1; i <= n; ++i) {
        long long value = inf.readLong(-1LL, 1000000000LL, "A_i");
        ensuref(value == -1 || value >= 1,
                "A_%d must be -1 or in [1, 1000000000], got %lld", i, value);

        if (value == -1) {
            ensuref(penguin_index == -1, "multiple penguin positions: %d and %d",
                    penguin_index, i);
            penguin_index = i;
        }

        if (i == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    ensuref(penguin_index != -1, "missing penguin position marked by -1");
    ensuref(1 < penguin_index && penguin_index < n,
            "penguin position must not be at an endpoint, got %d", penguin_index);

    inf.readEof();
}
