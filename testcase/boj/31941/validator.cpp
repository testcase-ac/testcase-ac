#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: T, N
    long long T = inf.readLong(1LL, 1000000000000LL, "T");
    inf.readSpace();
    int N = inf.readInt(1, 1000000, "N");
    ensuref((long long)N <= T, "N (%d) must be <= T (%lld)", N, T);
    inf.readEoln();

    // Second line: L, K
    long long L = inf.readLong(1LL, 1000000000000LL, "L");
    inf.readSpace();
    int K = inf.readInt(2, 1000000, "K");
    ensuref((long long)K <= L + 1, "K (%d) must be <= L+1 (%lld)", K, L + 1);
    inf.readEoln();

    // Third line: t_i (dangerous turns)
    vector<long long> t(N);
    if (N > 0) {
        t = inf.readLongs(N, 0LL, T - 1, "t_i");
    }
    inf.readEoln();
    for (int i = 0; i + 1 < N; i++) {
        ensuref(t[i] < t[i+1],
                "t_i must be strictly increasing: t[%d]=%lld >= t[%d]=%lld",
                i, t[i], i+1, t[i+1]);
    }

    // Fourth line: l_j (permanent platforms)
    vector<long long> l(K);
    l = inf.readLongs(K, 0LL, L, "l_j");
    inf.readEoln();
    // Check endpoints
    ensuref(l.front() == 0LL,
            "First permanent platform l[0]=%lld must be 0", l.front());
    ensuref(l.back() == L,
            "Last permanent platform l[%d]=%lld must be L (%lld)",
            K-1, l.back(), L);
    // Check strictly increasing
    for (int i = 0; i + 1 < K; i++) {
        ensuref(l[i] < l[i+1],
                "l_j must be strictly increasing: l[%d]=%lld >= l[%d]=%lld",
                i, l[i], i+1, l[i+1]);
    }

    inf.readEof();
    return 0;
}
