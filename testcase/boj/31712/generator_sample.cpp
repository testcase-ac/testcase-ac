#include "testlib.h"

#include <array>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    array<int, 3> c;
    array<int, 3> d;
    int h;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        int totalDamage = 0;
        for (int i = 0; i < 3; ++i) {
            c[i] = rnd.next(1, 1000);
            d[i] = rnd.next(c[i], 1000);
            totalDamage += d[i];
        }
        h = rnd.next(1, totalDamage);
    } else if (mode == 1) {
        int period = rnd.next(1, 30);
        int totalDamage = 0;
        for (int i = 0; i < 3; ++i) {
            c[i] = period;
            d[i] = rnd.next(period, 1000);
            totalDamage += d[i];
        }
        h = rnd.next(totalDamage + 1, 5000);
    } else if (mode == 2) {
        for (int i = 0; i < 3; ++i) {
            c[i] = rnd.next(1, 12);
            d[i] = rnd.next(c[i], c[i] + rnd.next(0, 25));
        }
        h = rnd.next(1, 5000);
    } else if (mode == 3) {
        for (int i = 0; i < 3; ++i) {
            c[i] = rnd.next(850, 1000);
            d[i] = rnd.next(c[i], 1000);
        }
        h = rnd.next(3000, 5000);
    } else {
        for (int i = 0; i < 3; ++i) {
            c[i] = rnd.next(1, 1000);
            d[i] = rnd.next(c[i], 1000);
        }
        h = rnd.next(1, 5000);
    }

    for (int i = 0; i < 3; ++i) {
        println(c[i], d[i]);
    }
    println(h);

    return 0;
}
