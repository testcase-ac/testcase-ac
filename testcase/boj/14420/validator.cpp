#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(2LL, 1000000000LL, "N");
    inf.readSpace();
    int m = inf.readInt(2, 3000, "M");
    inf.readSpace();
    int k = inf.readInt(m, 3000, "K");
    inf.readEoln();

    ensuref(k <= n, "K must not exceed N: K=%d, N=%lld", k, n);

    long long a = inf.readLong(1LL, 1000000000LL, "A");
    inf.readSpace();
    long long b = inf.readLong(1LL, 1000000000LL, "B");
    inf.readSpace();
    long long c = inf.readLong(1LL, 1000000000LL, "C");
    inf.readEoln();

    ensuref(b < c, "expected B < C, got B=%lld, C=%lld", b, c);
    ensuref(c < a, "expected C < A, got C=%lld, A=%lld", c, a);

    inf.readLong(1LL, 1000000000000000000LL, "T");
    inf.readEoln();

    vector<long long> s(m);
    for (int i = 0; i < m; ++i) {
        s[i] = inf.readLong(1LL, n, "S_i");
        inf.readEoln();

        if (i > 0) {
            ensuref(s[i - 1] < s[i],
                    "express stops must be strictly increasing: S_%d=%lld, S_%d=%lld",
                    i, s[i - 1], i + 1, s[i]);
        }
    }

    ensuref(s.front() == 1, "S_1 must be 1, got %lld", s.front());
    ensuref(s.back() == n, "S_M must be N, got S_M=%lld, N=%lld", s.back(), n);

    inf.readEof();
}
