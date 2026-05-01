#include "testlib.h"
using namespace std;

long long sampleBase(int scaleType) {
    if (scaleType == 0) { // small
        return rnd.next(-20, 20);
    } else if (scaleType == 1) { // medium
        return rnd.next(-2000, 2000);
    } else { // large
        return rnd.next(-100000000, 100000000);
    }
}

struct Inequality {
    long long A, B, C;
};

// Create inequality equivalent (for integer solutions) to x >= L
Inequality makeLower(long long L) {
    long long val = llabs(L) + 1; // >=1
    long long Knatural = 1000000000LL / val;
    if (Knatural < 1) Knatural = 1;

    long long kmax;
    if (rnd.next(0, 99) < 70) {
        kmax = min(1000LL, Knatural);
    } else {
        kmax = Knatural;
    }
    if (kmax < 1) kmax = 1;
    long long k = rnd.next(1LL, kmax); // |A| = k

    long long t;
    if (k == 1 || rnd.next(0, 1) == 0) {
        t = 0;
    } else {
        long long tmax = min(k - 1, 5LL);
        t = rnd.next(1LL, tmax);
    }

    // D = B - C = k*L - t, with 0 <= t < k
    long long D = k * L - t;
    long long Dabs = llabs(D);
    long long M = 1000000000LL - Dabs;
    if (M < 0) M = 0;
    long long B = 0;
    if (M > 0) B = rnd.next(-M, M);
    long long C = B - D;

    Inequality ineq;
    ineq.A = -k;
    ineq.B = B;
    ineq.C = C;
    return ineq;
}

// Create inequality equivalent (for integer solutions) to x <= R
Inequality makeUpper(long long R) {
    long long val = llabs(R) + 1; // >=1
    long long Knatural = 1000000000LL / val;
    if (Knatural < 1) Knatural = 1;

    long long kmax;
    if (rnd.next(0, 99) < 70) {
        kmax = min(1000LL, Knatural);
    } else {
        kmax = Knatural;
    }
    if (kmax < 1) kmax = 1;
    long long k = rnd.next(1LL, kmax); // A = k > 0

    long long t;
    if (k == 1 || rnd.next(0, 1) == 0) {
        t = 0;
    } else {
        long long tmax = min(k - 1, 5LL);
        t = rnd.next(1LL, tmax);
    }

    // D = C - B = k*R + t, with 0 <= t < k
    long long D = k * R + t;
    long long Dabs = llabs(D);
    long long M = 1000000000LL - Dabs;
    if (M < 0) M = 0;
    long long B = 0;
    if (M > 0) B = rnd.next(-M, M);
    long long C = B + D;

    Inequality ineq;
    ineq.A = k;
    ineq.B = B;
    ineq.C = C;
    return ineq;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Inequality> cons;

    int roll = rnd.next(0, 99);
    int scenario; // 0 = finite, 1 = infinite, 2 = empty
    if (roll < 50) scenario = 0;
    else if (roll < 80) scenario = 1;
    else scenario = 2;

    if (scenario == 0) {
        // Finite number of integer solutions
        int scaleType = rnd.next(0, 2);
        long long L = sampleBase(scaleType);
        long long width = rnd.next(0, 10);
        long long R = L + width; // ensure L <= R

        int N = rnd.next(2, 12);

        // One tight lower and one tight upper bound
        cons.push_back(makeLower(L));
        cons.push_back(makeUpper(R));

        for (int i = 2; i < N; ++i) {
            bool makeLowerFlag = (rnd.next(0, 1) == 0);
            if (makeLowerFlag) {
                // Redundant or equal lower bound
                long long L2 = L - rnd.next(0, 10); // L2 <= L
                cons.push_back(makeLower(L2));
            } else {
                // Redundant or equal upper bound
                long long R2 = R + rnd.next(0, 10); // R2 >= R
                cons.push_back(makeUpper(R2));
            }
        }
    } else if (scenario == 1) {
        // Infinite integer solutions
        int dir = rnd.next(0, 1); // 0: only lowers (no upper), 1: only uppers (no lower)
        int scaleType = rnd.next(0, 2);
        int N = rnd.next(1, 12);

        if (dir == 0) {
            // Only lower bounds: x >= something, unbounded above
            long long baseL = sampleBase(scaleType);
            cons.push_back(makeLower(baseL));
            for (int i = 1; i < N; ++i) {
                long long L2 = baseL + rnd.next(-10, 10);
                cons.push_back(makeLower(L2));
            }
        } else {
            // Only upper bounds: x <= something, unbounded below
            long long baseR = sampleBase(scaleType);
            cons.push_back(makeUpper(baseR));
            for (int i = 1; i < N; ++i) {
                long long R2 = baseR + rnd.next(-10, 10);
                cons.push_back(makeUpper(R2));
            }
        }
    } else {
        // Empty set of integer solutions
        int scaleType = rnd.next(0, 2);
        long long base = sampleBase(scaleType);
        long long gap = rnd.next(0, 10);
        long long R = base;
        long long L = base + 1 + gap; // L > R

        int N = rnd.next(2, 12);

        // One lower bound forcing x >= L, one upper forcing x <= R
        cons.push_back(makeLower(L));
        cons.push_back(makeUpper(R));

        for (int i = 2; i < N; ++i) {
            bool makeLowerFlag = (rnd.next(0, 1) == 0);
            if (makeLowerFlag) {
                long long L2 = L + rnd.next(-10, 10);
                cons.push_back(makeLower(L2));
            } else {
                long long R2 = R + rnd.next(-10, 10);
                cons.push_back(makeUpper(R2));
            }
        }
    }

    // Shuffle inequalities to avoid any pattern
    shuffle(cons.begin(), cons.end());

    println((int)cons.size());
    for (auto &ineq : cons) {
        println(ineq.A, ineq.B, ineq.C);
    }

    return 0;
}
