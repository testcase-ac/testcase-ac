#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);

    int N = 0;
    vector<long long> A, B;

    if (mode == 0) {
        // Very small, hand-checkable
        N = rnd.next(1, 4);
        A.assign(N, 0);
        B.assign(N, 0);
        for (int i = 0; i < N; ++i) {
            A[i] = rnd.next(1, 10);
            B[i] = rnd.next(1, 10);
        }
    } else if (mode == 1) {
        // Random medium-sized values
        N = rnd.next(5, 15);
        A.assign(N, 0);
        B.assign(N, 0);
        for (int i = 0; i < N; ++i) {
            A[i] = rnd.next(1, 1000);
            B[i] = rnd.next(1, 1000);
        }
    } else if (mode == 2) {
        // Random large values in full range
        N = rnd.next(5, 15);
        A.assign(N, 0);
        B.assign(N, 0);
        for (int i = 0; i < N; ++i) {
            A[i] = rnd.next(1, 1000000000);
            B[i] = rnd.next(1, 1000000000);
        }
    } else if (mode == 3) {
        // All B_i equal, A_i around multiples of B
        N = rnd.next(3, 10);
        A.assign(N, 0);
        B.assign(N, 0);
        int baseB = rnd.next(1, 20);
        for (int i = 0; i < N; ++i) {
            int k = rnd.next(1, 20);
            int choice = rnd.next(0, 2); // 0,1,2 -> -1,0,1
            int delta = choice - 1;
            long long val = 1LL * k * baseB + delta;
            if (val < 1) val = 1;
            A[i] = val;
            B[i] = baseB;
        }
    } else if (mode == 4) {
        // All trees finish in 1 day (A_i <= B_i)
        N = rnd.next(1, 10);
        A.assign(N, 0);
        B.assign(N, 0);
        for (int i = 0; i < N; ++i) {
            int bi = rnd.next(1, 20);
            int ai = rnd.next(1, bi);
            A[i] = ai;
            B[i] = bi;
        }
    } else if (mode == 5) {
        // One dominating tree, others trivial
        N = rnd.next(2, 10);
        A.assign(N, 0);
        B.assign(N, 0);
        int mainIdx = rnd.next(0, N - 1);
        for (int i = 0; i < N; ++i) {
            if (i == mainIdx) {
                int bi = rnd.next(1, 50);
                int k = rnd.next(20, 80);
                long long base = 1LL * bi * k;
                int extra = rnd.next(0, bi - 1);
                long long ai = base + extra;
                if (ai <= 0) ai = 1;
                A[i] = ai;
                B[i] = bi;
            } else {
                int bi = rnd.next(1, 50);
                int ai = rnd.next(1, bi * 2);
                A[i] = ai;
                B[i] = bi;
            }
        }
    } else if (mode == 6) {
        // Carefully crafted so that for some D, sum max(0, t0_i - D) == D
        // where t0_i = ceil(A_i / B_i)
        N = rnd.next(3, 10);
        A.assign(N, 0);
        B.assign(N, 0);

        int D = rnd.next(2, 20);
        int m = rnd.next(1, min(N, D)); // number of trees with t0_i > D

        vector<long long> t0(N, 0);
        vector<long long> excess(m, 0);

        int rem = D - m; // remaining excess after assigning 1 to each
        for (int r = 0; r < rem; ++r) {
            int j = rnd.next(0, m - 1);
            excess[j]++;
        }

        for (int j = 0; j < m; ++j) {
            t0[j] = D + excess[j]; // > D
        }
        for (int i = m; i < N; ++i) {
            t0[i] = rnd.next(1, D); // <= D
        }

        // Assign B_i and derive A_i so that ceil(A_i / B_i) == t0_i
        for (int i = 0; i < N; ++i) {
            int bi = rnd.next(1, 30);
            B[i] = bi;
            long long ti = t0[i];
            // A in ((t0-1)*B, t0*B] to keep ceil == t0
            int add = rnd.next(1, bi);
            A[i] = (ti - 1) * bi + add;
        }

        // Shuffle trees to hide structure
        vector<int> ord(N);
        for (int i = 0; i < N; ++i) ord[i] = i;
        shuffle(ord.begin(), ord.end());
        vector<long long> A2(N), B2(N);
        for (int i = 0; i < N; ++i) {
            A2[i] = A[ord[i]];
            B2[i] = B[ord[i]];
        }
        A.swap(A2);
        B.swap(B2);
    }

    // Optional scaling to push some tests toward larger values while keeping constraints
    if (rnd.next(0, 4) == 0) { // 20% chance
        long long maxA = 0, maxB = 0;
        for (int i = 0; i < (int)A.size(); ++i) {
            if (A[i] > maxA) maxA = A[i];
            if (B[i] > maxB) maxB = B[i];
        }
        if (maxA == 0) maxA = 1;
        if (maxB == 0) maxB = 1;
        long long maxMulA = 1000000000LL / maxA;
        long long maxMulB = 1000000000LL / maxB;
        long long maxMul = maxMulA < maxMulB ? maxMulA : maxMulB;

        if (maxMul > 1) {
            long long upper = maxMul;
            if (upper > 1000000LL) upper = 1000000LL; // avoid too huge factors
            if (upper >= 2) {
                int s = rnd.next(2, (int)upper);
                for (int i = 0; i < (int)A.size(); ++i) {
                    A[i] *= s;
                    B[i] *= s;
                }
            }
        }
    }

    println(N);
    println(A);
    println(B);

    return 0;
}
