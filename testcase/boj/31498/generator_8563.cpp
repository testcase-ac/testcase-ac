#include "testlib.h"
using namespace std;

struct TestCase {
    long long A, B, C, D, K;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAXA  = 1000000000000LL;
    const long long MAXC  = 1000000000000LL;
    const long long MAXBD = 1000000000LL;

    long long A, B, C, D, K;

    int kind = rnd.next(0, 7);

    switch (kind) {
        // A few fixed, hand-crafted small cases (including samples)
        case 0: {
            vector<TestCase> fixed = {
                {100, 50, 10, 50, 10}, // sample 1: caught
                {100, 50, 10, 35, 10}, // sample 2: escape in 3
                {10,  3,  0,  4,  1},  // small, C=0
                {20,  5,  5,  3,  2},  // small mixed
                {7,   3,  0,  2,  0}   // K=0, C=0
            };
            TestCase t = rnd.any(fixed);
            A = t.A; B = t.B; C = t.C; D = t.D; K = t.K;
            break;
        }

        // Small random parameters
        case 1: {
            A = rnd.next(1LL, 200LL);
            B = rnd.next(1LL, 50LL);
            C = rnd.next(0LL, 200LL);
            D = rnd.next(1LL, 50LL);
            K = rnd.next(0LL, B);
            break;
        }

        // Large-scale parameters near constraints (overflow / precision traps)
        case 2: {
            A = rnd.next(MAXA / 10, MAXA);       // [1e11, 1e12]
            B = rnd.next(MAXBD / 10, MAXBD);     // [1e8, 1e9]
            C = rnd.next(0LL, MAXC);
            D = rnd.next(MAXBD / 10, MAXBD);     // [1e8, 1e9]
            int typeK = rnd.next(0, 2);
            if (typeK == 0) K = 0;
            else if (typeK == 1) K = B;
            else K = rnd.next(0LL, B);
            break;
        }

        // K = 0 (constant speed for Toka)
        case 3: {
            A = rnd.next(1LL, 400LL);
            B = rnd.next(1LL, 100LL);
            C = rnd.next(0LL, 400LL);
            D = rnd.next(1LL, 100LL);
            K = 0;
            break;
        }

        // K = B (Toka has at most one non-zero move)
        case 4: {
            B = rnd.next(1LL, 100LL);
            bool oneStepFinish = (rnd.next(0, 1) == 0);
            if (oneStepFinish) {
                // Can reach house in one move
                A = rnd.next(1LL, B);
            } else {
                // Cannot reach in one move
                A = rnd.next(B + 1, 3 * B);
            }
            C = rnd.next(0LL, 3 * B);
            D = rnd.next(1LL, 100LL);
            K = B;
            break;
        }

        // C = 0 (start at the same position, not initially caught)
        case 5: {
            A = rnd.next(1LL, 200LL);
            B = rnd.next(1LL, 100LL);
            C = 0;
            D = rnd.next(1LL, 100LL);
            K = rnd.next(0LL, B);
            break;
        }

        // Large C (Doldol is far behind), small A
        case 6: {
            A = rnd.next(1LL, 200LL);
            B = rnd.next(1LL, 100LL);
            D = rnd.next(1LL, 100LL);
            K = rnd.next(0LL, B);
            bool huge = (rnd.next(0, 1) == 0);
            if (huge) {
                C = rnd.next(100000000LL, MAXC); // very far behind
            } else {
                C = rnd.next(A, A + 500);        // moderately behind
                if (C > MAXC) C = MAXC;
            }
            break;
        }

        // Deliberate "overtake without equal position at end of step" pattern
        case 7: {
            A = rnd.next(10LL, 50LL);
            C = rnd.next(1LL, 5LL);
            B = rnd.next(1LL, 5LL);
            long long minD = B + C + 1;
            long long maxD = A + C - 1;
            if (minD > maxD) maxD = minD;
            D = rnd.next(minD, maxD);
            K = rnd.next(0LL, B);
            break;
        }
    }

    println(A, B);
    println(C, D);
    println(K);

    return 0;
}
