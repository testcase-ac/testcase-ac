#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int R = 0, S = 0;
    int mode = rnd.next(0, 5); // choose scenario

    auto findCase = [&](int minT, int maxT) {
        const int maxR = 20;
        const int maxS = 20;
        int r, s, t;
        bool found = false;

        for (int it = 0; it < 10000 && !found; ++it) {
            r = rnd.next(0, maxR);
            s = rnd.next(0, maxS);
            t = 8 * r + 3 * s;
            if (t >= minT && t <= maxT) {
                found = true;
                R = r;
                S = s;
            }
        }

        if (!found) {
            for (r = 0; r <= maxR && !found; ++r) {
                for (s = 0; s <= maxS && !found; ++s) {
                    t = 8 * r + 3 * s;
                    if (t >= minT && t <= maxT) {
                        found = true;
                        R = r;
                        S = s;
                    }
                }
            }
        }
    };

    switch (mode) {
        case 0:
            // Exact 28 cupcakes: no leftovers
            findCase(28, 28);
            break;
        case 1:
            // Small leftover (1..5), total just above 28
            findCase(29, 33);
            break;
        case 2:
            // Moderate total but < 56 to keep hand-checkable
            findCase(34, 55);
            break;
        case 3:
            // Larger total >= 56 to catch modulo-28 type bugs
            findCase(56, 80);
            break;
        case 4:
            // Only regular boxes
            S = 0;
            R = rnd.next(4, 10); // 32..80 cupcakes
            break;
        case 5:
            // Only small boxes
            R = 0;
            S = rnd.next(10, 15); // 30..45 cupcakes
            break;
    }

    // Ensure validity (at least 28 cupcakes)
    int total = 8 * R + 3 * S;
    if (total < 28) {
        // Fallback: simple valid case
        R = 4;
        S = 0;
    }

    println(R);
    println(S);

    return 0;
}
