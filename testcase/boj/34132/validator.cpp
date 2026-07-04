#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readSpace();
    inf.readInt(1, 17012, "R");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        long long mUpperBound = 1000000000LL;
        long long a = inf.readLong(0LL, mUpperBound - 1, "A_i");
        inf.readSpace();
        long long b = inf.readLong(0LL, mUpperBound - 1, "B_i");
        inf.readSpace();
        long long initial = inf.readLong(0LL, mUpperBound - 1, "I_i");
        inf.readSpace();
        long long m = inf.readLong(1LL, mUpperBound, "M_i");
        inf.readEoln();

        ensuref(a < m, "A_%d must be less than M_%d: %lld >= %lld", i, i, a, m);
        ensuref(b < m, "B_%d must be less than M_%d: %lld >= %lld", i, i, b, m);
        ensuref(initial < m, "I_%d must be less than M_%d: %lld >= %lld", i, i, initial, m);
    }

    inf.readEof();
}
