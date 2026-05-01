#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // 1) Choose N small for readability
    int N = rnd.next(1, 12);

    // 2) Choose K with bias to edge cases K=1 or K=N
    int K;
    if (N == 1) {
        K = 1;
    } else {
        int p = rnd.next(1, 100);
        if (p <= 20) K = 1;
        else if (p <= 40) K = N;
        else K = rnd.next(1, N);
    }

    // 3) Choose weight scale
    ll maxW;
    int tier = rnd.next(1, 3);
    if (tier == 1) {
        maxW = rnd.next(1LL, 10LL);
    } else if (tier == 2) {
        maxW = rnd.next(10LL, 10000LL);
    } else {
        maxW = rnd.next(10000LL, 1000000LL);
    }

    // 4) Generate A with some duplicate probability
    double dupProb = rnd.next(0.0, 1.0);
    vector<ll> A;
    A.reserve(N);
    vector<ll> seen;
    for (int i = 0; i < N; i++) {
        ll v;
        if (!seen.empty() && rnd.next() < dupProb) {
            v = rnd.any(seen);
        } else {
            v = rnd.next(1LL, maxW);
        }
        A.push_back(v);
        seen.push_back(v);
    }

    // 5) Compute sums for hyper-parameter intervals
    ll sumAll = 0;
    ll maxAi = 0;
    for (ll v : A) {
        sumAll += v;
        maxAi = max(maxAi, v);
    }
    vector<ll> B = A;
    sort(B.begin(), B.end(), greater<ll>());
    ll sumK = 0;
    for (int i = 0; i < K; i++) sumK += B[i];

    ll sumAllCap = min(sumAll, 1000000LL);

    // Build candidate intervals for C, all clipped to [1, 1e6]
    vector<pair<ll,ll>> intervals;
    auto add_interval = [&](ll lo, ll hi) {
        lo = max(lo, 1LL);
        hi = min(hi, 1000000LL);
        if (lo <= hi) intervals.emplace_back(lo, hi);
    };

    // Always allow [1, maxAi]
    add_interval(1, maxAi);
    // Interval from maxAi to sumK
    add_interval(maxAi, sumK);
    // Interval above sumK to sumAllCap
    add_interval(sumK + 1, sumAllCap);

    // Pick one interval and sample C
    auto iv = rnd.any(intervals);
    ll C = rnd.next(iv.first, iv.second);

    // Output
    println(N, K, C);
    println(A);

    return 0;
}
