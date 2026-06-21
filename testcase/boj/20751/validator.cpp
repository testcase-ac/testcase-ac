#include "testlib.h"

#include <cstdlib>

using namespace std;

long long manhattan(long long a, long long b, long long c, long long d) {
    return llabs(a - c) + llabs(b - d);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 2000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        long long n = inf.readLong(1LL, 1000000000LL, "N");
        inf.readSpace();
        long long m = inf.readLong(1LL, 1000000000LL, "M");
        inf.readSpace();
        long long r = inf.readLong(1LL, n, "R");
        inf.readSpace();
        long long c = inf.readLong(1LL, m, "C");
        inf.readSpace();
        long long s = inf.readLong(1LL, 1000000000LL, "S");
        inf.readEoln();

        ensuref(manhattan(r, c, 1LL, 1LL) > s,
                "Tuzik can reach Barsik's starting cell in test %d", i);
        ensuref(manhattan(r, c, n, m) > s,
                "Tuzik can reach Barsik's food cell in test %d", i);
    }

    inf.readEof();
}
