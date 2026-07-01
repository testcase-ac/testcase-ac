#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long A = inf.readLong(1LL, 1000000000000LL, "A");
    inf.readSpace();
    long long B = inf.readLong(A, 1000000000000LL, "B");
    inf.readSpace();
    inf.readLong(2LL, B, "P");
    inf.readEoln();

    ensuref(B <= A + 1000000LL, "B must be at most A + 1000000: A=%lld, B=%lld", A, B);

    inf.readEof();
}
