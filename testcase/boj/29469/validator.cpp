#include "testlib.h"

using namespace std;

// Factorize k (<= 1e9) safely into prime powers
vector<pair<long long,int>> factorize(long long k) {
    vector<pair<long long,int>> res;
    for (long long p = 2; p * p <= k; ++p) {
        if (k % p == 0) {
            int cnt = 0;
            while (k % p == 0) {
                k /= p;
                ++cnt;
            }
            res.push_back({p, cnt});
        }
    }
    if (k > 1) res.push_back({k, 1});
    return res;
}

// Exponent of prime p in N! via Legendre formula.
// N up to 1e18, p up to 1e9 -> fits in 64-bit, but use __int128 for sums.
long long exponentInFactorial(long long N, long long p) {
    __int128 sum = 0;
    while (N) {
        N /= p;
        sum += N;
    }
    long long ans = (long long)sum;
    ensuref(ans >= 0, "overflow or negative exponent in factorial");
    return ans;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test: two integers N and k on one line
    long long N = inf.readLong(1LL, 1000000000000000000LL, "N"); // 1..1e18
    inf.readSpace();
    long long k = inf.readLong(2LL, 1000000000LL, "k");          // 2..1e9
    inf.readEoln();

    // Global property: the answer (number of trailing zeros) always exists and fits in 64-bit.
    // We'll compute it and also implicitly check no undefined behavior (e.g., k=1) occurs.

    // Factorize k
    vector<pair<long long,int>> fac = factorize(k);

    ensuref(!fac.empty(), "factorization of k failed");

    // Compute minimal exponent ratio over all prime factors
    long long answer = -1;
    for (auto [p, cnt] : fac) {
        long long e = exponentInFactorial(N, p);
        long long val = e / cnt;
        if (answer == -1 || val < answer) answer = val;
    }

    // Additional sanity: answer should be >= 0
    ensuref(answer >= 0, "computed negative answer for N=%lld, k=%lld", N, k);

    // We don't output anything here, just validate input.

    inf.readEof();
}
