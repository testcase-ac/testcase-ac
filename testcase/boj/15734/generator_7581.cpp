#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int variant = rnd.next(0, 6);
    int L, R, A;
    switch (variant) {
        case 0:
            // All zero
            L = 0; R = 0; A = 0;
            break;
        case 1:
            // All max
            L = 100; R = 100; A = 100;
            break;
        case 2:
            // Only ambidextrous
            L = 0; R = 0;
            A = rnd.next(0, 100);
            break;
        case 3:
            // One side zero
            if (rnd.next(0, 1) == 0) {
                L = 0;
                R = rnd.next(1, 100);
            } else {
                R = 0;
                L = rnd.next(1, 100);
            }
            A = rnd.next(0, 100);
            break;
        case 4:
            // Already balanced L == R
            L = rnd.next(0, 100);
            R = L;
            A = rnd.next(0, 100);
            break;
        case 5: {
            // Difference strictly greater than A
            L = rnd.next(0, 100);
            do {
                R = rnd.next(0, 100);
            } while (R == L);
            int diff = L > R ? L - R : R - L;
            A = rnd.next(0, diff - 1);
            break;
        }
        case 6: {
            // A large enough to cover the difference
            L = rnd.next(0, 100);
            do {
                R = rnd.next(0, 100);
            } while (R == L);
            int diff = L > R ? L - R : R - L;
            A = rnd.next(diff, 100);
            break;
        }
    }

    println(L, R, A);
    return 0;
}
