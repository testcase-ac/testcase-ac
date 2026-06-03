#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        long long s = inf.readLong(0LL, 1000000000LL, "S");
        inf.readSpace();
        long long e = inf.readLong(0LL, 1000000000LL, "E");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "C");
        inf.readEoln();

        ensuref(s < e, "route %d must satisfy S < E, got S=%lld E=%lld", i + 1, s, e);
    }

    inf.readEof();
}
