#include "testlib.h"

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

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000LL, "n");
    inf.readSpace();
    long long m = inf.readLong(1LL, 1000000000LL, "m");
    inf.readSpace();
    long long t = inf.readLong(1LL, 1000000000LL, "t");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000LL, "k");
    inf.readEoln();

    ensuref(computeRevenue(n, m, t, k) <= 2000000000LL,
            "answer exceeds 2000000000");

    inf.readEof();
}
