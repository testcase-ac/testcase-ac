#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        long long s = inf.readLong(0LL, 1000000000LL, "S_i");
        inf.readSpace();
        long long e = inf.readLong(1LL, 1000000000LL, "E_i");
        inf.readSpace();
        inf.readInt(1, 1000, "C_i");
        inf.readEoln();

        ensuref(s < e, "contest %d must satisfy S_i < E_i, got %lld >= %lld", i, s, e);
    }

    inf.readEof();
}
