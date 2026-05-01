#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int h1, w1, h2, w2;

    int type = rnd.next(0, 9);

    switch (type) {
        // Fully random over full constraints
        case 0: {
            h1 = rnd.next(2, 50);
            w1 = rnd.next(2, 50);
            h2 = rnd.next(1, h1 - 1);
            w2 = rnd.next(1, w1 - 1);
            break;
        }
        // Small dimensions, easy to reason about
        case 1: {
            h1 = rnd.next(2, 10);
            w1 = rnd.next(2, 10);
            h2 = rnd.next(1, h1 - 1);
            w2 = rnd.next(1, w1 - 1);
            break;
        }
        // Near-square outer shape
        case 2: {
            h1 = rnd.next(2, 50);
            int base = h1;
            int diff;
            do {
                diff = rnd.next(-2, 2);
                w1 = base + diff;
            } while (w1 < 2 || w1 > 50);
            h2 = rnd.next(1, h1 - 1);
            w2 = rnd.next(1, w1 - 1);
            break;
        }
        // Very thin missing part: one side of inner rectangle is 1
        case 3: {
            h1 = rnd.next(2, 50);
            w1 = rnd.next(2, 50);
            int style = rnd.next(0, 2);
            if (style == 0) {
                h2 = 1;
                w2 = rnd.next(1, w1 - 1);
            } else if (style == 1) {
                w2 = 1;
                h2 = rnd.next(1, h1 - 1);
            } else {
                h2 = 1;
                w2 = 1;
            }
            break;
        }
        // Large dimensions both directions
        case 4: {
            h1 = rnd.next(30, 50);
            w1 = rnd.next(30, 50);
            h2 = rnd.next(1, h1 - 1);
            w2 = rnd.next(1, w1 - 1);
            break;
        }
        // Inner vertical size almost equals outer (thin vertical arm)
        case 5: {
            h1 = rnd.next(20, 50);
            w1 = rnd.next(2, 50);
            h2 = rnd.next(h1 - 3, h1 - 1); // difference 1..3
            w2 = rnd.next(1, w1 - 1);
            break;
        }
        // w1 - w2 is small (thin horizontal arm)
        case 6: {
            h1 = rnd.next(2, 50);
            w1 = rnd.next(3, 50);          // allow delta up to 2
            int delta = rnd.next(1, 2);    // w1 - w2 = 1 or 2
            w2 = w1 - delta;
            h2 = rnd.next(1, h1 - 1);
            break;
        }
        // Both differences are 1 (missing 1x1 corner)
        case 7: {
            h1 = rnd.next(2, 50);
            w1 = rnd.next(2, 50);
            h2 = h1 - 1;
            w2 = w1 - 1;
            break;
        }
        // Exactly the sample tests (chosen randomly among them)
        case 8: {
            int samples[3][4] = {
                {8, 7, 3, 2},
                {5, 3, 1, 1},
                {5, 5, 1, 2}
            };
            int idx = rnd.next(0, 2);
            h1 = samples[idx][0];
            w1 = samples[idx][1];
            h2 = samples[idx][2];
            w2 = samples[idx][3];
            break;
        }
        // Outer square or near-square, inner roughly half
        case 9: {
            int side = rnd.next(10, 50);
            h1 = side;
            int diff;
            do {
                diff = rnd.next(-1, 1);
                w1 = side + diff;
            } while (w1 < 2 || w1 > 50);
            h2 = rnd.next(1, h1 - 1);
            w2 = rnd.next(1, w1 - 1);
            break;
        }
    }

    // Final safety: if any constraint is accidentally broken, fall back to fully random.
    if (!(2 <= h1 && h1 <= 50 && 2 <= w1 && w1 <= 50 &&
          1 <= h2 && h2 < h1 && 1 <= w2 && w2 < w1)) {
        h1 = rnd.next(2, 50);
        w1 = rnd.next(2, 50);
        h2 = rnd.next(1, h1 - 1);
        w2 = rnd.next(1, w1 - 1);
    }

    println(h1, w1, h2, w2);

    return 0;
}
