#include "testlib.h"
#include <vector>
#include <cstdint>
#include <algorithm>
#include <limits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(3, 10000, "N");
    inf.readEoln();

    // Read the second-circle numbers a[0..N-1]
    vector<long long> a(N);
    for (int i = 0; i < N; i++) {
        a[i] = inf.readLong(1LL, 1000000000LL - 1, "a_i");
        inf.readEoln();
    }

    // We know a_i are the sums of each number and its two neighbors in the first circle:
    // a[i] = b[i-1] + b[i] + b[i+1]  (indices mod N), and b[i] are positive integers.
    //
    // We must check that there exists at least one positive-integer solution b[0..N-1].
    //
    // This is a cyclic tri-diagonal linear system.  One can handle two cases:
    // 1) N % 3 != 0: the system has a unique solution, which we solve and check.
    // 2) N % 3 == 0: the system has infinitely many solutions iff certain consistency
    //    (gamma_N == 0 && gamma_{N+1} == 0) holds.  Then one must check that there is
    //    at least one positive solution.  One can reduce positivity constraints to:
    //      b0 > -gamma[i]    for i % 3 == 0
    //      b1 > -gamma[i]    for i % 3 == 1
    //      b0 + b1 < gamma[i] for i % 3 == 2
    //    which yields simple bounds on b0, b1 and a feasibility check.
    //
    // We implement this in O(N) time.

    // Build gamma array: gamma[0]=0, gamma[1]=0, and for i>=2:
    //   gamma[i] = a[i-1 mod N] - gamma[i-1] - gamma[i-2].
    // We extend to i = N and N+1 for closure checks.
    vector<long long> gamma(N+2);
    gamma[0] = 0;
    gamma[1] = 0;
    for (int i = 2; i <= N+1; i++) {
        int ai = (i-1) % N;
        // gamma[i] = a[ai] - gamma[i-1] - gamma[i-2]
        __int128 tmp = (__int128)a[ai] - gamma[i-1] - gamma[i-2];
        // It fits in int64 since |gamma| <= O(N * max a) ~ 1e13
        gamma[i] = (long long)tmp;
    }

    if (N % 3 == 0) {
        // Consistency condition for infinite-family case
        ensuref(gamma[N] == 0 && gamma[N+1] == 0,
                "No solution exists: gamma[N]=%lld, gamma[N+1]=%lld", gamma[N], gamma[N+1]);

        // Derive positivity constraints:
        // For i % 3 == 0: b[i] = b0 + gamma[i] > 0  => b0 > -gamma[i]
        // For i % 3 == 1: b[i] = b1 + gamma[i] > 0  => b1 > -gamma[i]
        // For i % 3 == 2: b[i] = -b0 - b1 + gamma[i] > 0 => b0 + b1 < gamma[i]

        long long LB_b0 = 1; // must be >=1 anyway
        long long LB_b1 = 1;
        // initialize UB_sum = +inf, then we take min
        long long UB_sum = std::numeric_limits<long long>::max();
        for (int i = 0; i < N; i++) {
            if (i % 3 == 0) {
                // b0 > -gamma[i]
                long long need = -gamma[i] + 1;
                LB_b0 = max(LB_b0, need);
            } else if (i % 3 == 1) {
                // b1 > -gamma[i]
                long long need = -gamma[i] + 1;
                LB_b1 = max(LB_b1, need);
            } else {
                // b0 + b1 < gamma[i]
                long long need_up = gamma[i] - 1;
                UB_sum = min(UB_sum, need_up);
            }
        }
        ensuref(LB_b0 >= 1,
                "No positive b0 possible: LB_b0=%lld", LB_b0);
        ensuref(LB_b1 >= 1,
                "No positive b1 possible: LB_b1=%lld", LB_b1);

        // We need LB_b0 + LB_b1 <= UB_sum for any feasible (b0,b1).
        __int128 sumLB = ( __int128 )LB_b0 + LB_b1;
        ensuref(sumLB <= UB_sum,
                "No positive solution: LB_b0+LB_b1=%lld > UB_sum=%lld",
                (long long)sumLB, UB_sum);

        // If all above holds, there is at least one positive solution, as guaranteed.

    } else {
        // Unique-solution case: solve 2x2 for b0,b1
        // Closure equations coefficients come from the recurrence
        // alpha_i, beta_i are periodic with period 3: alpha: [1,0,-1], beta: [0,1,-1]
        auto alpha = [&](int idxMod3) {
            if (idxMod3 == 0) return 1LL;
            if (idxMod3 == 1) return 0LL;
            return -1LL; // idxMod3 == 2
        };
        auto beta = [&](int idxMod3) {
            if (idxMod3 == 0) return 0LL;
            if (idxMod3 == 1) return 1LL;
            return -1LL; // idxMod3 == 2
        };
        long long aN = alpha(N % 3);
        long long bN = beta(N % 3);
        long long aNp1 = alpha((N+1) % 3);
        long long bNp1 = beta((N+1) % 3);

        // Eq1: (aN - 1)*b0 + bN*b1 = -gamma[N]
        // Eq2: aNp1*b0 + (bNp1 - 1)*b1 = -gamma[N+1]
        long long C11 = aN - 1;
        long long C12 = bN;
        long long D1  = -gamma[N];
        long long C21 = aNp1;
        long long C22 = bNp1 - 1;
        long long D2  = -gamma[N+1];

        // determinant
        __int128 det128 = (__int128)C11 * C22 - (__int128)C12 * C21;
        long long det = (long long)det128;
        ensuref(det != 0,
                "No unique solution: det=%lld", det);

        // Solve with Cramer's rule
        __int128 num0 = (__int128)D1 * C22 - (__int128)C12 * D2;
        __int128 num1 = (__int128)C11 * D2 - (__int128)D1 * C21;
        // Check integrality
        ensuref(num0 % det == 0,
                "b0 not integer: num0=%lld det=%lld", (long long)num0, det);
        ensuref(num1 % det == 0,
                "b1 not integer: num1=%lld det=%lld", (long long)num1, det);
        long long b0 = (long long)(num0 / det);
        long long b1 = (long long)(num1 / det);

        // Must be positive
        ensuref(b0 >= 1,
                "b0 <= 0: b0=%lld", b0);
        ensuref(b1 >= 1,
                "b1 <= 0: b1=%lld", b1);

        // Reconstruct full b[0..N-1] and verify positivity and that all equations match
        vector<long long> b(N);
        b[0] = b0;
        b[1] = b1;
        for (int i = 2; i < N; i++) {
            // b[i] = a[i-1] - b[i-1] - b[i-2]
            __int128 t = (__int128)a[i-1] - b[i-1] - b[i-2];
            b[i] = (long long)t;
        }
        // Check all positivity
        for (int i = 0; i < N; i++) {
            ensuref(b[i] >= 1,
                    "b[%d] <= 0: %lld", i, b[i]);
        }
        // Check all a[i] == b[i-1] + b[i] + b[i+1]
        for (int i = 0; i < N; i++) {
            int im = (i-1+N)%N, ip = (i+1)%N;
            __int128 sum = (__int128)b[im] + b[i] + b[ip];
            ensuref(sum == a[i],
                    "Equation mismatch at i=%d: a[%d]=%lld vs sum b[%d]+b[%d]+b[%d]=%lld",
                    i, i, a[i], im, i, ip, (long long)sum);
        }
    }

    // End of file
    inf.readEof();
    return 0;
}
