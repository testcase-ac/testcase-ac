#include "testlib.h"
#include <algorithm>

using namespace std;

static __int128 computeRevenue(long long n, long long m, long long t, long long k) {
    long long fullBatchesTotal = n / m;
    long long remainder = n % m;
    long long totalBatches = fullBatchesTotal + (remainder > 0 ? 1 : 0);
    long long profitableBatches = min(totalBatches, (k - 1) / t + 1);

    long long fullProfitableBatches = min(fullBatchesTotal, profitableBatches);
    __int128 batchCount = fullProfitableBatches;
    __int128 revenue = (__int128)m *
                       (batchCount * k - (__int128)t * batchCount * (batchCount - 1) / 2);

    if (remainder > 0 && profitableBatches > fullBatchesTotal) {
        revenue += (__int128)remainder * (k - (__int128)fullBatchesTotal * t);
    }

    return revenue;
}

static bool valid(long long n, long long m, long long t, long long k) {
    return computeRevenue(n, m, t, k) <= 2000000000LL;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long n = 1, m = 1, t = 1, k = 1;
    int mode = rnd.next(0, 7);

    for (int attempt = 0; attempt < 1000; ++attempt) {
        if (mode == 0) {
            n = rnd.next(1LL, 30LL);
            m = rnd.next(1LL, 30LL);
            t = rnd.next(1LL, 30LL);
            k = rnd.next(1LL, 30LL);
        } else if (mode == 1) {
            n = rnd.next(1LL, 200LL);
            m = rnd.next(n, 1000000000LL);
            t = rnd.next(1LL, 1000000000LL);
            k = rnd.next(1LL, max(1LL, 2000000000LL / n));
        } else if (mode == 2) {
            m = 1;
            n = rnd.next(1LL, 200000LL);
            t = rnd.next(1LL, 1000LL);
            k = rnd.next(1LL, 100000LL);
        } else if (mode == 3) {
            m = rnd.next(2LL, 50LL);
            long long batches = rnd.next(2LL, 80LL);
            long long rem = rnd.next(1LL, m - 1);
            n = m * batches + rem;
            t = rnd.next(1LL, 1000LL);
            k = rnd.next(1LL, 100000LL);
        } else if (mode == 4) {
            k = rnd.next(1LL, 1000000000LL);
            t = rnd.next(k, 1000000000LL);
            m = rnd.next(1LL, max(1LL, 2000000000LL / k));
            n = rnd.next(m, 1000000000LL);
        } else if (mode == 5) {
            n = 1000000000LL;
            m = rnd.next(1LL, 5LL);
            t = rnd.next(1LL, 3LL);
            k = rnd.next(1LL, 70000LL);
        } else if (mode == 6) {
            t = 1000000000LL;
            k = rnd.next(1LL, 1000000000LL);
            long long paidLimit = max(1LL, 2000000000LL / k);
            m = rnd.next(1LL, min(1000000000LL, paidLimit));
            n = rnd.next(m, 1000000000LL);
        } else {
            n = rnd.next(1LL, 100000LL);
            m = rnd.next(1LL, 1000LL);
            t = rnd.next(1LL, 100000LL);
            k = rnd.next(1LL, 100000LL);
        }

        if (valid(n, m, t, k)) break;
    }

    if (!valid(n, m, t, k)) {
        n = 7;
        m = 2;
        t = 3;
        k = 7;
    }

    println(n, m, t, k);
    return 0;
}
