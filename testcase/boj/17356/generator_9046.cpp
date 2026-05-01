#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int A = 0, B = 0;
    int type = rnd.next(1, 8);

    switch (type) {
        case 1: {
            // Example 1
            A = 2000; B = 1800;
            break;
        }
        case 2: {
            // Example 2
            A = 1655; B = 3015;
            break;
        }
        case 3: {
            // Equal strengths
            A = rnd.next(0, 5000);
            B = A;
            break;
        }
        case 4: {
            // One at extreme, other random
            if (rnd.next(0, 1) == 0) {
                A = 0;
                B = rnd.next(0, 5000);
            } else {
                A = 5000;
                B = rnd.next(0, 5000);
            }
            break;
        }
        case 5: {
            // Both small
            A = rnd.next(0, 100);
            B = rnd.next(0, 100);
            break;
        }
        case 6: {
            // Both in mid/high range
            A = rnd.next(1000, 4000);
            B = rnd.next(1000, 4000);
            break;
        }
        case 7: {
            // Very small difference |A-B| <= 10
            do {
                A = rnd.next(0, 5000);
                int delta = rnd.next(-10, 10);
                B = A + delta;
            } while (B < 0 || B > 5000);
            break;
        }
        case 8: {
            // Ensure (B-A) is NOT a multiple of 400 (to expose integer-division bugs)
            while (true) {
                A = rnd.next(0, 5000);
                B = rnd.next(0, 5000);
                int diff = B - A;
                int mod = diff % 400;
                if (mod < 0) mod += 400;
                if (mod != 0) break;
            }
            break;
        }
    }

    println(A, B);
    return 0;
}
