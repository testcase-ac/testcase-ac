#include "testlib.h"
using namespace std;

const long long MAXV = 1000000000LL;

// Compute floor( (S / k)^k ), clipped at MAXV+1 as sentinel
long long pmax_floor_clipped(long long S, int k) {
    double base = (double)S / (double)k;
    double val = 1.0;
    for (int i = 0; i < k; ++i) {
        val *= base;
        if (val > (double)MAXV + 1e6) {
            return MAXV + 1; // sentinel: bigger than allowed range
        }
    }
    long long r = (long long)(val + 1e-9); // floor for positive values
    if (r > MAXV + 1) r = MAXV + 1;
    return r;
}

// Generate a pair (S, P) such that there exists a list of size n
// and no list of any smaller size; n in [3, 12] inside this function.
bool genTargetMinN(long long &S, long long &P) {
    for (int it = 0; it < 100; ++it) {
        S = rnd.next(10, 200);       // moderate S for readability
        int n = rnd.next(3, 12);     // target minimal size

        vector<long long> pmax(n + 1);
        for (int k = 1; k <= n; ++k) {
            pmax[k] = pmax_floor_clipped(S, k);
        }

        long long L = 0; // max floor(Pmax(k)) for k < n
        for (int k = 1; k < n; ++k) {
            if (pmax[k] > L) L = pmax[k];
        }
        long long R = pmax[n];
        if (R > MAXV) R = MAXV;

        if (R <= L || R < 1) continue;

        long long low = L + 1;
        if (low < 1) low = 1;
        long long high = R;
        if (low > high) continue;

        P = rnd.next(low, high);
        return true;
    }
    return false;
}

// Generate a feasible (S, P) using some n in [2, 8], not controlling minimal n.
bool genFeasibleRandom(long long &S, long long &P) {
    for (int it = 0; it < 100; ++it) {
        int n = rnd.next(2, 8);
        S = rnd.next((long long)n, 500LL); // keep S moderate

        double base = (double)S / (double)n;
        double val = 1.0;
        for (int i = 0; i < n; ++i) {
            val *= base;
            if (val > (double)MAXV + 1e6) break;
        }
        if (val < 1.0) continue;

        long long R = (long long)(val + 1e-9);
        if (R < 1) continue;
        if (R > MAXV) R = MAXV;

        P = rnd.next(1LL, R);
        return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long S = 0, P = 0;

    int pick = rnd.next(1, 100);

    if (pick <= 20) {
        // Scenario 1: S == P (minimal size 1)
        if (rnd.next(0, 1) == 0)
            S = rnd.next(1LL, 50LL);                     // small
        else
            S = rnd.next(MAXV - 100LL, MAXV);            // near upper bound
        P = S;
    } else if (pick <= 40) {
        // Scenario 2: two-element integer-friendly case
        long long a = rnd.next(1, 50);
        long long b = rnd.next(1, 50);
        S = a + b;
        P = a * b;
    } else if (pick <= 65) {
        // Scenario 3: targeted minimal n >= 3
        if (!genTargetMinN(S, P)) {
            if (!genFeasibleRandom(S, P)) {
                // Fallback: simple S == P
                S = rnd.next(1LL, 50LL);
                P = S;
            }
        }
    } else if (pick <= 80) {
        // Scenario 4: impossible case (no list exists)
        // Use small S, compute global max product and choose P above it.
        S = rnd.next(2, 30);
        double best = 0.0;
        for (int n = 1; n <= (int)S; ++n) {
            double base = (double)S / (double)n;
            double val = 1.0;
            for (int i = 0; i < n; ++i) val *= base;
            if (val > best) best = val;
        }
        long long K = (long long)(best + 1e-9); // floor
        if (K >= MAXV) K = MAXV - 1; // very safe for S <= 30
        P = rnd.next(K + 1, MAXV);   // strictly greater than all achievable products
    } else if (pick <= 90) {
        // Scenario 5: general feasible via inequality, random n
        if (!genFeasibleRandom(S, P)) {
            S = rnd.next(1LL, 50LL);
            P = S;
        }
    } else {
        // Scenario 6: high boundary random values near 1e9
        S = rnd.next(MAXV - 200LL, MAXV);
        P = rnd.next(MAXV - 200LL, MAXV);
    }

    println(S, P);
    return 0;
}
