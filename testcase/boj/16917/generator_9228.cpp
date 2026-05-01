#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int A, B, C, X, Y;

    int type = rnd.next(0, 8);

    switch (type) {
        case 0: {
            // Completely random within constraints
            A = rnd.next(1, 5000);
            B = rnd.next(1, 5000);
            C = rnd.next(1, 5000);
            X = rnd.next(1, 100000);
            Y = rnd.next(1, 100000);
            break;
        }
        case 1: {
            // Small values, easy to check by hand
            A = rnd.next(1, 20);
            B = rnd.next(1, 20);
            C = rnd.next(1, 20);
            X = rnd.next(1, 20);
            Y = rnd.next(1, 20);
            break;
        }
        case 2: {
            // Half-and-half clearly best for both kinds (2C <= A and 2C <= B)
            int base = rnd.next(1000, 4000);
            A = base;
            B = base + rnd.next(-200, 200); // small variation but stay in [1,5000]
            if (B < 1) B = 1;
            if (B > 5000) B = 5000;
            int mx = min(A, B) / 2;
            if (mx < 1) mx = 1;
            C = rnd.next(1, mx);
            X = rnd.next(50000, 100000);
            Y = rnd.next(50000, 100000);
            break;
        }
        case 3: {
            // Half-and-half clearly never useful (C > max(A, B))
            A = rnd.next(1, 4000);
            B = rnd.next(1, 4000);
            int lo = max(A, B) + 1;
            if (lo > 5000) lo = 5000;
            C = rnd.next(lo, 5000);
            X = rnd.next(1, 100000);
            Y = rnd.next(1, 100000);
            break;
        }
        case 4: {
            // Half-and-half better than A, worse than B (only substitute A)
            // Fixed pattern to ensure inequalities: 2C > B and 2C < A
            B = 500;
            A = 4000;
            C = rnd.next(251, 1999); // ensures 502 <= 2C <= 3998
            X = rnd.next(1, 100000);
            Y = rnd.next(1, 100000);
            break;
        }
        case 5: {
            // Half-and-half better than B, worse than A (only substitute B)
            A = 500;
            B = 4000;
            C = rnd.next(251, 1999);
            X = rnd.next(1, 100000);
            Y = rnd.next(1, 100000);
            break;
        }
        case 6: {
            // Very unbalanced required counts
            A = rnd.next(1, 5000);
            B = rnd.next(1, 5000);
            C = rnd.next(1, 5000);
            if (rnd.next(0, 1) == 0) {
                X = 100000;
                Y = rnd.next(1, 5);
            } else {
                X = rnd.next(1, 5);
                Y = 100000;
            }
            break;
        }
        case 7: {
            // Extremely cheap half-and-half compared to A and B
            A = rnd.next(4000, 5000);
            B = rnd.next(4000, 5000);
            C = rnd.next(1, min(10, min(A, B) / 3));
            if (C < 1) C = 1;
            X = rnd.next(50000, 100000);
            Y = rnd.next(50000, 100000);
            break;
        }
        case 8: {
            // Various boundary cases with equalities involving 2C
            int variant = rnd.next(0, 2);
            if (variant == 0) {
                // 2C == A
                C = rnd.next(1, 2500);
                A = 2 * C;
                B = rnd.next(1, 5000);
            } else if (variant == 1) {
                // 2C == B
                C = rnd.next(1, 2500);
                B = 2 * C;
                A = rnd.next(1, 5000);
            } else {
                // 2C == A + B
                while (true) {
                    A = rnd.next(1, 5000);
                    B = rnd.next(1, 5000);
                    int sum = A + B;
                    if (sum % 2 == 0 && sum / 2 <= 5000) {
                        C = sum / 2;
                        break;
                    }
                }
            }
            X = rnd.next(1, 100000);
            Y = rnd.next(1, 100000);
            break;
        }
        default: {
            // Fallback: random
            A = rnd.next(1, 5000);
            B = rnd.next(1, 5000);
            C = rnd.next(1, 5000);
            X = rnd.next(1, 100000);
            Y = rnd.next(1, 100000);
            break;
        }
    }

    println(A, B, C, X, Y);
    return 0;
}
