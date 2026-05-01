#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int y = 0, c = 0, p = 0;

    int mode = rnd.next(1, 9);

    switch (mode) {
        case 1: {
            // All zeros
            y = c = p = 0;
            break;
        }
        case 2: {
            // Only one type non-zero (small or very large)
            int which = rnd.next(0, 2);
            int val;
            if (rnd.next(0, 1) == 0)
                val = rnd.next(1, 20);
            else
                val = rnd.next(1000000 - 20, 1000000);
            if (which == 0) y = val;
            else if (which == 1) c = val;
            else p = val;
            break;
        }
        case 3: {
            // Perfectly balanced small case: answer easy to see
            int k = rnd.next(0, 10);
            y = k;
            c = 2 * k;
            p = k;
            break;
        }
        case 4: {
            // C/2 is the limiting factor (small)
            int k = rnd.next(0, 10);
            c = 2 * k;
            int up = min(1000, k + 10);
            y = rnd.next(k, up);
            p = rnd.next(k, up);
            break;
        }
        case 5: {
            // Y is the limiting factor (small)
            y = rnd.next(0, 10);
            int cup = min(1000, 2 * y + 20);
            int pup = min(1000, y + 20);
            c = rnd.next(2 * y, cup);
            p = rnd.next(y, pup);
            break;
        }
        case 6: {
            // P is the limiting factor (small)
            p = rnd.next(0, 10);
            int yup = min(1000, p + 20);
            int cup = min(1000, 2 * p + 20);
            y = rnd.next(p, yup);
            c = rnd.next(2 * p, cup);
            break;
        }
        case 7: {
            // Completely random small to medium
            y = rnd.next(0, 50);
            c = rnd.next(0, 50);
            p = rnd.next(0, 50);
            break;
        }
        case 8: {
            // Completely random up to the maximum
            y = rnd.next(0, 1000000);
            c = rnd.next(0, 1000000);
            p = rnd.next(0, 1000000);
            break;
        }
        case 9: {
            // C is odd, testing floor(c/2) behavior
            int k = rnd.next(0, 10);
            c = 2 * k + 1; // odd
            int low = k + 1;
            int up = min(1000, k + 11);
            y = rnd.next(low, up);
            p = rnd.next(low, up);
            break;
        }
    }

    println(y, c, p);
    return 0;
}
