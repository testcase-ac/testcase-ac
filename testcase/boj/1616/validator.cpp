#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(2, 10000000, "K");
    inf.readSpace();
    int m = inf.readInt(1, 23, "M");
    inf.readEoln();

    long long combinations = 1;
    for (int i = 0; i < m; ++i) {
        combinations *= k;
        ensuref(combinations <= 10000000,
                "K^M must be at most 10000000, got more than that at exponent %d",
                i + 1);
    }

    inf.readEof();
}
