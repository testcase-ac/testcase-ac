#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and T
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    long long T = inf.readLong(1LL, 1000000000LL, "T");
    inf.readEoln();

    vector<long long> L(N), R(N);
    for (int i = 0; i < N; ++i) {
        L[i] = inf.readLong(1LL, 1000000LL, "L_i");
        inf.readSpace();
        R[i] = inf.readLong(1LL, 1000000LL, "R_i");
        inf.readEoln();
        ensuref(L[i] <= R[i], "At line %d: L_i (%lld) must be <= R_i (%lld)", i + 2, L[i], R[i]);
    }

    // Global feasibility: there must exist some allocation with Li <= ai <= Ri, sum ai = T
    long long sumL = 0, sumR = 0;
    for (int i = 0; i < N; ++i) {
        sumL += L[i];
        sumR += R[i];
    }
    ensuref(sumL <= T && T <= sumR,
            "Global feasibility violated: no allocation with Li<=ai<=Ri summing to T (sumL=%lld, sumR=%lld, T=%lld)",
            sumL, sumR, T);

    // Additionally check that there exists some S and allocation with ai <= S.
    // This is implied by existence of S in the problem; we validate it.
    // For a given S, feasibility reduces to:
    //   sum max(Li, 0) <= T <= sum min(Ri, S)   but also ai >= Li, ai <= min(Ri, S)
    //
    // S must be at least max_i Li, at most max_i Ri.
    long long maxL = 0, maxR = 0;
    for (int i = 0; i < N; ++i) {
        maxL = max(maxL, L[i]);
        maxR = max(maxR, R[i]);
    }

    auto feasibleWithS = [&](long long S) -> bool {
        long long minSum = 0;
        long long maxSum = 0;
        for (int i = 0; i < N; ++i) {
            long long hi = min(R[i], S);
            if (hi < L[i]) return false; // impossible for this person
            minSum += L[i];
            maxSum += hi;
            if (minSum > T) return false;
            if (maxSum >= T && minSum <= T) {
                // still must continue to ensure no later hi < Li, but we already checked hi<Li above
                // so we can continue
                ;
            }
        }
        return (minSum <= T && T <= maxSum);
    };

    bool existsS = false;
    // S range: [maxL, maxR] (if S < maxL, some Li>S impossible; if S>maxR, same as S=maxR)
    long long lo = maxL, hi = maxR;
    while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        if (feasibleWithS(mid)) {
            existsS = true;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    ensuref(existsS,
            "Problem guarantee violated: no S exists such that there is an allocation with Li<=ai<=min(Ri,S) and sum ai=T");

    inf.readEof();
}
