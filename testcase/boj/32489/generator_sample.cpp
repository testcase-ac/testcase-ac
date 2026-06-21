#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampPitch(int value) {
    return max(-200000, min(200000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 25);
    vector<int> t(n);
    t[0] = 0;

    if (mode == 0) {
        int drift = rnd.next(-3, 3);
        int wiggle = rnd.next(0, 2);
        for (int i = 1; i < n; ++i) {
            t[i] = clampPitch(i + drift * i + rnd.next(-wiggle, wiggle));
        }
    } else if (mode == 1) {
        int base = rnd.next(-12, 12);
        for (int i = 1; i < n; ++i) {
            t[i] = clampPitch(i + base + rnd.next(-8, 8));
        }
    } else if (mode == 2) {
        int lo = rnd.next(-30, 0);
        int hi = rnd.next(0, 30);
        for (int i = 1; i < n; ++i) {
            t[i] = rnd.next(lo, hi);
        }
    } else if (mode == 3) {
        vector<int> choices = {-200000, -199999, -100000, -1, 0, 1, 100000, 199999, 200000};
        for (int i = 1; i < n; ++i) {
            t[i] = rnd.any(choices);
        }
    } else if (mode == 4) {
        int pivot = rnd.next(2, n);
        int firstSlope = rnd.next(-6, 6);
        int secondSlope = rnd.next(-6, 6);
        for (int i = 1; i < n; ++i) {
            int slope = i < pivot ? firstSlope : secondSlope;
            t[i] = clampPitch(slope * i + rnd.next(-5, 5));
        }
    } else {
        int a = rnd.next(-20, 20);
        int b = rnd.next(-20, 20);
        for (int i = 1; i < n; ++i) {
            t[i] = (i % 2 == 0) ? clampPitch(i + a) : clampPitch(-i + b);
        }
        shuffle(t.begin() + 1, t.end());
    }

    println(n);
    println(t);

    return 0;
}
