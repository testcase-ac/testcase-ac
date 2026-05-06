#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <cstdint>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the number of real divisors k
    int k = inf.readInt(1, 50, "k");
    inf.readEoln();

    // Read the k divisors, each in [2, 1e6]
    vector<long long> divs = inf.readLongs(k, 2LL, 1000000LL, "d_i");
    inf.readEoln();

    // Check for duplicates
    {
        set<long long> seen;
        for (int i = 0; i < k; i++) {
            long long d = divs[i];
            ensuref(!seen.count(d),
                    "Duplicate divisor detected: d_%d = %lld",
                    i+1, d);
            seen.insert(d);
        }
    }

    // Find the minimum and maximum divisor
    long long mn = *min_element(divs.begin(), divs.end());
    long long mx = *max_element(divs.begin(), divs.end());

    // Compute N = mn * mx, check it fits in signed 32-bit
    __int128 prod = ( __int128 ) mn * mx;
    ensuref(prod <= 2147483647LL,
            "Computed N = %lld * %lld = %lld exceeds 32-bit signed limit",
            mn, mx, (long long)prod);
    long long N = (long long) prod;

    // Check each given divisor actually divides N
    for (int i = 0; i < k; i++) {
        long long d = divs[i];
        ensuref(N % d == 0,
                "Given divisor d_%d = %lld does not divide computed N = %lld",
                i+1, d, N);
    }

    // Compute all real divisors of N (i.e., divisors in (1, N))
    vector<long long> real_divs;
    for (long long i = 2; i * i <= N; i++) {
        if (N % i == 0) {
            real_divs.push_back(i);
            long long j = N / i;
            if (j != i && j != N) {
                real_divs.push_back(j);
            }
        }
    }
    // Sort both lists and compare
    sort(real_divs.begin(), real_divs.end());
    vector<long long> orig = divs;
    sort(orig.begin(), orig.end());

    ensuref((int)real_divs.size() == k,
            "Number of real divisors mismatch: expected %d, found %d for N = %lld",
            k, (int)real_divs.size(), N);

    for (int i = 0; i < k; i++) {
        ensuref(real_divs[i] == orig[i],
                "Divisor mismatch at index %d: expected %lld, found %lld for N = %lld",
                i, real_divs[i], orig[i], N);
    }

    inf.readEof();
    return 0;
}
