#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter for N: sometimes 1, small, or medium
    int N;
    int pick = rnd.next(0, 3);
    if (pick == 0) {
        N = 1;
    } else if (pick == 1) {
        N = rnd.next(2, 5);
    } else {
        N = rnd.next(6, 10);
    }

    // Generate each player's cards with independent distribution types
    auto genCards = [&](int n) {
        vector<long long> v(n);
        int dist = rnd.next(0, 2);
        if (dist == 0) {
            // Uniform up to a random max
            long long m = rnd.any(vector<long long>{10, 1000, 1000000000LL});
            for (int i = 0; i < n; i++)
                v[i] = rnd.next(1LL, m);
        } else if (dist == 1) {
            // Small range [1,10]
            for (int i = 0; i < n; i++)
                v[i] = rnd.next(1LL, 10LL);
        } else {
            // Cluster around a base
            long long base = rnd.next(1LL, 1000000000LL);
            long long delta = rnd.next(0LL, 1000LL);
            long long lo = max(1LL, base - delta);
            long long hi = base + delta;
            for (int i = 0; i < n; i++)
                v[i] = rnd.next(lo, hi);
        }
        // Ordering hyperparameter: random, sorted, or reverse
        intord:
        int order = rnd.next(0, 2);
        if (order == 1) {
            sort(v.begin(), v.end());
        } else if (order == 2) {
            sort(v.begin(), v.end());
            reverse(v.begin(), v.end());
        }
        return v;
    };

    vector<long long> A = genCards(N);
    vector<long long> B = genCards(N);
    vector<long long> C = genCards(N);

    // Generate K with varied strategies
    long long K;
    int kcase = rnd.next(0, 3);
    if (kcase == 0) {
        // Small K
        K = rnd.next(1LL, 50LL);
    } else if (kcase == 1) {
        // Sum of three random cards
        int i = rnd.next(0, N-1);
        int j = rnd.next(0, N-1);
        int k = rnd.next(0, N-1);
        K = A[i] + B[j] + C[k];
    } else if (kcase == 2) {
        // Near 1e9
        long long lo = max(1LL, 1000000000LL - 1000LL);
        long long hi = 1000000000LL + 1000LL;
        K = rnd.next(lo, hi);
    } else {
        // Large K up to 3e9
        K = rnd.next(1000000000LL, 3000000000LL);
    }

    // Output
    println(N, K);
    println(A);
    println(B);
    println(C);

    return 0;
}
