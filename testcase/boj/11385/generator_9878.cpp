#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = 0, M = 0;
    int type = rnd.next(0, 8); // choose scenario 0..8

    if (type == 0) {
        // Tiny, very small coefficients
        N = 1; M = 1;
    } else if (type == 1) {
        // Very small degrees, small coefficients
        N = rnd.next(1, 3);
        M = rnd.next(1, 3);
    } else if (type == 2) {
        // Random small degrees
        N = rnd.next(1, 8);
        M = rnd.next(1, 8);
    } else if (type == 3) {
        // Geometric progression
        N = rnd.next(5, 15);
        M = rnd.next(5, 15);
    } else if (type == 4) {
        // Small degrees, very large coefficients (overflow trap)
        N = rnd.next(1, 5);
        M = rnd.next(1, 5);
    } else if (type == 5) {
        // Mixed small and very large coefficients
        N = rnd.next(3, 10);
        M = rnd.next(3, 10);
    } else if (type == 6) {
        // Mostly ones with a single huge coefficient
        N = rnd.next(5, 20);
        M = rnd.next(5, 20);
    } else if (type == 7) {
        // Monotone (mostly) decreasing sequences
        N = rnd.next(5, 20);
        M = rnd.next(5, 20);
    } else { // type == 8
        // Unbalanced degrees
        N = rnd.next(10, 20);
        M = rnd.next(1, 5);
    }

    vector<int> a(N + 1), b(M + 1);

    if (type == 0) {
        // Tiny, random small
        for (int i = 0; i <= N; ++i)
            a[i] = rnd.next(1, 10);
        for (int i = 0; i <= M; ++i)
            b[i] = rnd.next(1, 10);
    } else if (type == 1) {
        // Structured tiny polynomials
        for (int i = 0; i <= N; ++i)
            a[i] = i + 1;          // 1,2,3,...
        for (int i = 0; i <= M; ++i)
            b[i] = (i + 1) * (i + 1); // 1,4,9,...
    } else if (type == 2) {
        // Random small coefficients
        for (int i = 0; i <= N; ++i)
            a[i] = rnd.next(1, 20);
        for (int i = 0; i <= M; ++i)
            b[i] = rnd.next(1, 20);
    } else if (type == 3) {
        // Geometric progression, capped at 1e6
        int baseA = rnd.next(2, 5);
        int baseB = rnd.next(2, 5);
        long long val = 1;
        for (int i = 0; i <= N; ++i) {
            if (i == 0) val = 1;
            else {
                val *= baseA;
                if (val > 1000000LL) val = 1000000LL;
            }
            a[i] = (int)val;
        }
        val = 1;
        for (int i = 0; i <= M; ++i) {
            if (i == 0) val = 1;
            else {
                val *= baseB;
                if (val > 1000000LL) val = 1000000LL;
            }
            b[i] = (int)val;
        }
    } else if (type == 4) {
        // All very large, to force 64-bit handling
        for (int i = 0; i <= N; ++i)
            a[i] = rnd.next(500000, 1000000);
        for (int i = 0; i <= M; ++i)
            b[i] = rnd.next(500000, 1000000);
    } else if (type == 5) {
        // Mixed tiny and huge
        for (int i = 0; i <= N; ++i) {
            if (rnd.next(0, 1) == 0)
                a[i] = rnd.next(1, 5);
            else
                a[i] = rnd.next(500000, 1000000);
        }
        for (int i = 0; i <= M; ++i) {
            if (rnd.next(0, 1) == 0)
                b[i] = rnd.next(1, 5);
            else
                b[i] = rnd.next(500000, 1000000);
        }
    } else if (type == 6) {
        // Mostly ones with a single huge spike in each polynomial
        for (int i = 0; i <= N; ++i) a[i] = 1;
        for (int i = 0; i <= M; ++i) b[i] = 1;
        int idxA = rnd.next(0, N);
        int idxB = rnd.next(0, M);
        a[idxA] = 1000000;
        b[idxB] = 1000000;
    } else if (type == 7) {
        // Decreasing-ish sequences
        int startA = rnd.next(100, 1000000);
        int stepA = max(1, startA / max(2, N + 1));
        for (int i = 0; i <= N; ++i) {
            long long v = (long long)startA - 1LL * stepA * i;
            if (v < 1) v = 1;
            a[i] = (int)min(1000000LL, v);
        }
        int startB = rnd.next(100, 1000000);
        int stepB = max(1, startB / max(2, M + 1));
        for (int i = 0; i <= M; ++i) {
            long long v = (long long)startB - 1LL * stepB * i;
            if (v < 1) v = 1;
            b[i] = (int)min(1000000LL, v);
        }
    } else { // type == 8
        // Unbalanced degrees, medium coefficients
        for (int i = 0; i <= N; ++i)
            a[i] = rnd.next(1, 100);
        for (int i = 0; i <= M; ++i)
            b[i] = rnd.next(1, 100);
    }

    println(N, M);
    println(a);
    println(b);

    return 0;
}
