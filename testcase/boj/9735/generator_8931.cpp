#include "testlib.h"
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

long long evalCubic(long long A, long long B, long long C, long long D, long long x) {
    return (((A * x + B) * x + C) * x + D);
}

int pickLeadingCoeff() {
    static vector<int> cand = {-5, -4, -3, -2, -1, 1, 2, 3, 4, 5};
    return rnd.any(cand);
}

// Type A: three distinct integer roots, one of them is 1
array<int,4> genTypeA() {
    while (true) {
        int A = pickLeadingCoeff();
        int r1 = 1;

        vector<int> cand;
        for (int v = -10; v <= 10; ++v)
            if (v != 1) cand.push_back(v);
        shuffle(cand.begin(), cand.end());
        int r2 = cand[0];
        int r3 = cand[1];

        long long S1 = (long long)r1 + r2 + r3;
        long long S2 = (long long)r1 * r2 + (long long)r1 * r3 + (long long)r2 * r3;
        long long S3 = (long long)r1 * r2 * r3;

        long long Acoef = A;
        long long Bcoef = -A * S1;
        long long Ccoef =  A * S2;
        long long Dcoef = -A * S3;

        // Coefficients are guaranteed small, but keep them as int
        int Ai = (int)Acoef;
        int Bi = (int)Bcoef;
        int Ci = (int)Ccoef;
        int Di = (int)Dcoef;

        // Sanity: 1 must be an integer root
        if (evalCubic(Ai, Bi, Ci, Di, 1) != 0) continue;

        return {Ai, Bi, Ci, Di};
    }
}

// Type B: exactly one real root (1), others complex
array<int,4> genTypeB() {
    while (true) {
        int A = pickLeadingCoeff();
        int p = rnd.next(-5, 5);
        int q = rnd.next(1, 10);

        long long disc = 1LL * p * p - 4LL * q;
        if (disc >= 0) continue; // want complex conjugate pair

        // Expand A*(x-1)*(x^2 + p x + q)
        long long Acoef = A;
        long long Bcoef = A * (p - 1);
        long long Ccoef = A * (q - p);
        long long Dcoef = -A * q;

        int Ai = (int)Acoef;
        int Bi = (int)Bcoef;
        int Ci = (int)Ccoef;
        int Di = (int)Dcoef;

        if (evalCubic(Ai, Bi, Ci, Di, 1) != 0) continue;

        return {Ai, Bi, Ci, Di};
    }
}

// Type C: three real roots, one integer (1), two irrational
array<int,4> genTypeC() {
    while (true) {
        int A = pickLeadingCoeff();
        int p = rnd.next(-10, 10);
        int q = rnd.next(-10, 10);

        long long disc = 1LL * p * p - 4LL * q;
        if (disc <= 0) continue; // need two real roots

        long long rt = (long long)floor(sqrt((long double)disc) + 0.5L);
        if (rt * rt == disc) continue; // avoid perfect square -> irrational roots

        // Avoid integer roots of the quadratic in small range to keep them "clearly" non-integer
        bool hasSmallIntRoot = false;
        for (int r = -10; r <= 10; ++r) {
            long long v = 1LL * r * r + 1LL * p * r + q;
            if (v == 0) {
                hasSmallIntRoot = true;
                break;
            }
        }
        if (hasSmallIntRoot) continue;

        // Avoid 1 being a root of quadratic (would give multiplicity)
        if (1 + p + q == 0) continue;

        // Expand A*(x-1)*(x^2 + p x + q)
        long long Acoef = A;
        long long Bcoef = A * (p - 1);
        long long Ccoef = A * (q - p);
        long long Dcoef = -A * q;

        int Ai = (int)Acoef;
        int Bi = (int)Bcoef;
        int Ci = (int)Ccoef;
        int Di = (int)Dcoef;

        if (evalCubic(Ai, Bi, Ci, Di, 1) != 0) continue;

        return {Ai, Bi, Ci, Di};
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    if (rnd.next(0, 2) == 0)
        N = 1;
    else
        N = rnd.next(2, 8);

    println(N);
    for (int i = 0; i < N; ++i) {
        int t = rnd.next(0, 9);
        array<int,4> coef;
        if (t < 5) {          // ~50%: three integer roots including 1
            coef = genTypeA();
        } else if (t < 8) {   // ~30%: three real roots, one integer 1
            coef = genTypeC();
        } else {              // ~20%: only one real root (1)
            coef = genTypeB();
        }
        println(coef[0], coef[1], coef[2], coef[3]);
    }

    return 0;
}
