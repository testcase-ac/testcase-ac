#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_COUNT = 10000;
    const long long MAX_TIME = 10000000000000000LL;

    int n = inf.readInt(1, MAX_COUNT, "n");
    inf.readSpace();
    int k = inf.readInt(1, MAX_COUNT, "k");
    inf.readSpace();
    long long t1 = inf.readLong(0LL, MAX_TIME - 1, "t_1");
    inf.readSpace();
    long long t2 = inf.readLong(1LL, MAX_TIME, "t_2");
    inf.readEoln();

    ensuref(t1 < t2, "expected t_1 < t_2, got %lld >= %lld", t1, t2);
    ensuref(1LL * n * k <= 10000000LL,
            "expected n * k <= 10000000, got %lld",
            1LL * n * k);

    vector<long long> m(n);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        m[i] = inf.readLong(0LL, MAX_TIME - 1, "m_i");
        if (i > 0) {
            ensuref(m[i - 1] < m[i],
                    "expected strictly increasing m_i, got m_%d=%lld and m_%d=%lld",
                    i,
                    m[i - 1],
                    i + 1,
                    m[i]);
        }
    }
    inf.readEoln();

    for (int j = 0; j < k; ++j) {
        long long b = inf.readLong(0LL, MAX_TIME - 1, "b_j");
        inf.readSpace();
        long long e = inf.readLong(0LL, MAX_TIME - 1, "e_j");
        inf.readEoln();

        // CHECK: The statement extraction corrupts this relation as "b_j 1".
        // Intervals have nonzero length in the samples and problem description.
        ensuref(b < e,
                "expected b_j < e_j for interval %d, got %lld >= %lld",
                j + 1,
                b,
                e);
    }

    inf.readEof();
}
