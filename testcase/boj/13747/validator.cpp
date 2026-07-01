#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000000000000LL, "n");
    inf.readSpace();
    int k = inf.readInt(1, 200000, "k");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        long long a = inf.readLong(1LL, n, "a");
        inf.readSpace();
        long long b = inf.readLong(a, n, "b");
        inf.readEoln();
    }

    inf.readEof();
}
