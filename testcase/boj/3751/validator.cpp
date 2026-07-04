#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 7777, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        long long A = inf.readLong(1LL, 1000000000000LL, "A");
        inf.readSpace();
        long long B = inf.readLong(1LL, 1000000000000LL, "B");
        inf.readEoln();

        ensuref(A <= B, "A must be at most B, got A=%lld and B=%lld", A, B);
    }

    inf.readEof();
}
