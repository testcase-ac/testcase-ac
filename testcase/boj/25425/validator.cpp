#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX = 1000000000LL;

    long long n = inf.readLong(1LL, MAX, "N");
    inf.readSpace();
    long long m = inf.readLong(1LL, MAX, "M");
    inf.readSpace();
    long long a = inf.readLong(1LL, n * m, "a");
    inf.readSpace();
    long long k = inf.readLong(1LL, m, "K");
    inf.readEoln();

    ensuref(k <= a, "K must not exceed a: K=%lld, a=%lld", k, a);
    ensuref(a - k <= (n - 1) * m,
            "remaining players outside Junhyuk's team exceed other team capacity: a=%lld, K=%lld, N=%lld, M=%lld",
            a, k, n, m);

    inf.readEof();
}
