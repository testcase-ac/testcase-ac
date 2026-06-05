#include "testlib.h"

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

int randomCentInBand(int lo, int hi) {
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 24);
    if (mode == 5) {
        n = rnd.next(25, 80);
    }

    vector<int> cents(n);

    if (mode == 0) {
        vector<int> choices = {0, 1, 2, 50, 98, 99, 100};
        for (int i = 0; i < n; ++i) {
            cents[i] = rnd.any(choices);
        }
    } else if (mode == 1) {
        int a = rnd.any(vector<int>{0, 10, 25, 50, 75, 90, 100});
        int b = rnd.any(vector<int>{0, 10, 25, 50, 75, 90, 100});
        for (int i = 0; i < n; ++i) {
            cents[i] = (i % 2 == 0 ? a : b);
        }
    } else if (mode == 2) {
        int start = rnd.next(0, 100);
        int step = rnd.next(-7, 7);
        for (int i = 0; i < n; ++i) {
            int value = start + i * step;
            if (value < 0) value = 0;
            if (value > 100) value = 100;
            cents[i] = value;
        }
    } else if (mode == 3) {
        int center = rnd.next(0, 100);
        int radius = rnd.next(0, 12);
        int lo = max(0, center - radius);
        int hi = min(100, center + radius);
        for (int i = 0; i < n; ++i) {
            cents[i] = randomCentInBand(lo, hi);
        }
    } else if (mode == 4) {
        int split = rnd.next(0, n);
        int leftLo = rnd.next(0, 50);
        int leftHi = rnd.next(leftLo, 50);
        int rightLo = rnd.next(50, 100);
        int rightHi = rnd.next(rightLo, 100);
        for (int i = 0; i < n; ++i) {
            cents[i] = (i < split ? randomCentInBand(leftLo, leftHi) : randomCentInBand(rightLo, rightHi));
        }
    } else {
        for (int i = 0; i < n; ++i) {
            cents[i] = rnd.next(0, 100);
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        if (i) {
            putchar(' ');
        }
        printf("%d.%02d", cents[i] / 100, cents[i] % 100);
    }
    putchar('\n');

    return 0;
}
