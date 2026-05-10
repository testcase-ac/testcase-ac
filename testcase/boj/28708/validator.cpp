#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static const int MAX_A = 1000000;
static vector<bool> isPrime;

void buildSieve(int limit) {
    isPrime.assign(limit + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; 1LL * i * i <= limit; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= limit; j += i)
                isPrime[j] = false;
        }
    }
}

// Try to compute minimal K and verify existence of a valid operation
// This is used only to check the guaranteed-existence property, not for grading.
int computeMinK(const vector<int>& A) {
    int n = (int)A.size();
    int maxSum = 0;
    for (int x : A) maxSum = max(maxSum, x);
    maxSum = maxSum * 2 + 2;
    if ((int)isPrime.size() - 1 < maxSum) {
        buildSieve(maxSum);
    }

    int allOdd = 1, allEven = 1;
    for (int x : A) {
        if (x % 2 == 0) allOdd = 0;
        if (x % 2 == 1) allEven = 0;
    }

    auto okAll = [&](const vector<int>& B) -> bool {
        int n = (int)B.size();
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (isPrime[B[i] + B[j]])
                    return false;
        return true;
    };

    // Case 1: all even, no op needed
    if (allEven) return 0;

    // Case 2: all odd: need to flip parity of at least n-1 elements
    if (allOdd) {
        // Check K = n-1 is feasible (it must be by parity reasoning)
        // Choose any index to leave unchanged, say 0.
        vector<int> B = A;
        for (int i = 1; i < n; ++i) B[i]++;
        // By reasoning, all sums will be odd >= 3, but some could be prime.
        // However, problem statement guarantees answer always exists,
        // so for validation we only need to ensure there exists some K (not necessarily parity-based bound).
        // So fall through to generic search below.
    }

    // Generic search for minimal K (N <= 200, brute-force subsets by K is impossible).
    // Instead, exploit parity and primality:
    // Observation: prime sums are odd except 2.
    // Sum Ai+Aj can be 2 only if both are 1.
    // So we mainly need to avoid odd primes => avoid (odd, even) pairs summing to prime.
    //
    // A constructive algorithm:
    // Try K = 0,1,2 by direct search over indices; if not found, accept that
    // there exists some K (problem guarantee) and just return something >=0.
    int nOdd = 0, nEven = 0;
    for (int x : A) {
        if (x % 2) ++nOdd; else ++nEven;
    }

    // Check K = 0
    if (okAll(A)) return 0;

    // Check K = 1
    {
        vector<int> B = A;
        for (int i = 0; i < n; ++i) {
            B[i] = A[i] + 1;
            if (okAll(B)) return 1;
            B[i] = A[i];
        }
    }

    // Check K = 2
    {
        vector<int> B = A;
        for (int i = 0; i < n; ++i) {
            B[i] = A[i] + 1;
            for (int j = i + 1; j < n; ++j) {
                B[j] = A[j] + 1;
                if (okAll(B)) return 2;
                B[j] = A[j];
            }
            B[i] = A[i];
        }
    }

    // If not found with K <= 2, fall back: by problem's guarantee an answer exists,
    // but computing absolute minimal K might be complex.
    // For validator, it's enough to ensure there is at least one solution, not exact minimality.
    // We'll construct a simple always-valid operation:
    // Make all numbers even: increment all odd Ai.
    vector<int> B = A;
    int K = 0;
    for (int i = 0; i < n; ++i) {
        if (B[i] % 2 == 1) {
            B[i]++;
            ++K;
        }
    }
    // Now all even, sums are even. We must ensure no sum is 2 (impossible for even+even),
    // and for odd primes we're safe because sums are even.
    ensuref(okAll(B), "Constructed parity-based operation does not avoid primes");
    return K;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 200, "N");
    inf.readEoln();

    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        A[i] = inf.readInt(1, 1000000, "A_i");
        if (i + 1 < N) inf.readSpace();
    }
    inf.readEoln();

    // Global property: the statement implicitly guarantees that there exists an operation
    // (some K and indices) that makes all pairwise sums composite (non-prime).
    // We validate this by actually finding some operation and checking that such
    // configuration exists (not caring about indices, only existence).
    int K = computeMinK(A);
    ensuref(K >= 0 && K <= N,
            "Computed K out of range: %d (must be between 0 and N=%d)", K, N);

    inf.readEof();
}
