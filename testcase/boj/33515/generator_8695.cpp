#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T1, T2;
    int type = rnd.next(1, 7);

    switch (type) {
        case 1: {
            // Equal times (could be edge or middle)
            int x = rnd.next(1, 10000);
            T1 = x;
            T2 = x;
            break;
        }
        case 2: {
            // Small close times, T1 < T2
            int base = rnd.next(1, 20);
            int delta = rnd.next(1, 20);
            T1 = base;
            T2 = min(10000, base + delta);
            break;
        }
        case 3: {
            // Small close times, T1 > T2
            int base = rnd.next(1, 20);
            int delta = rnd.next(1, 20);
            T2 = base;
            T1 = min(10000, base + delta);
            break;
        }
        case 4: {
            // Extreme opposite edges
            if (rnd.next(0, 1) == 0) {
                T1 = 1; T2 = 10000;
            } else {
                T1 = 10000; T2 = 1;
            }
            break;
        }
        case 5: {
            // Both in mid-range, possibly equal, small variance
            int base = rnd.next(100, 500);
            int delta = rnd.next(-50, 50);
            T1 = base;
            T2 = base + delta;
            if (T2 < 1) T2 = 1;
            if (T2 > 10000) T2 = 10000;
            break;
        }
        case 6: {
            // Fully random in range
            T1 = rnd.next(1, 10000);
            T2 = rnd.next(1, 10000);
            break;
        }
        case 7: {
            // Edge-focused random: often near 1 or 10000
            auto pickEdge = []() {
                int mode = rnd.next(1, 3);
                if (mode == 1) return rnd.next(1, 10);           // very small
                if (mode == 2) return rnd.next(9991, 10000);     // very large
                return rnd.next(1, 10000);                       // anywhere
            };
            T1 = pickEdge();
            T2 = pickEdge();
            break;
        }
    }

    // Final safety to respect constraints
    if (T1 < 1) T1 = 1;
    if (T1 > 10000) T1 = 10000;
    if (T2 < 1) T2 = 1;
    if (T2 > 10000) T2 = 10000;

    println(T1, T2);
    return 0;
}
